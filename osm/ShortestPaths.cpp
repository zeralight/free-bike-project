#include <QTextStream>
#include <QThread>
#include <QSet>
#include <QtConcurrentMap>

#include <list>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <cassert>
#include <iostream>
#include <functional>

#include "ShortestPaths.hpp"
#include "OsmParser.hpp"

#ifdef DEBUG_ONLY_PROCESSED_NODES
#warning "DEBUG_ONLY_PROCESSED_NODES set"
#endif

namespace osm {

#ifdef DEBUG_ONLY_PROCESSED_NODES
    static long long processedNodes = 0;
#endif
#if defined(DEBUG_VELO) || defined(DEBUG_MISSING_PATHS)
    static long long notReachableRoutes = 0LL;
#endif

Nodes const* AllShortestPaths::pNodes = nullptr;
AdjacencyList const* AllShortestPaths::pEdges = nullptr;
std::vector<size_t> AllShortestPaths::bicycleNodes;
size_t AllShortestPaths::nbBicycleNodes = 0;
        
Paths AllShortestPaths::run(Nodes const& nodes, AdjacencyList const& edges) {
    nbBicycleNodes = 0;
    bicycleNodes.clear();
    pNodes = &nodes;
    pEdges = &edges;
    for (size_t i = 0; i < nodes.size(); ++i)
        if (nodes[i].isBicycleParking)
            ++nbBicycleNodes;
    bicycleNodes.reserve(nbBicycleNodes);
    for (size_t i = 0; i < nodes.size(); ++i) {
        auto const& n = nodes[i];
        if (n.isBicycleParking)
            bicycleNodes.push_back(i);
    }
    nbBicycleNodes = bicycleNodes.size();
    Paths res;
#ifndef QT_NO_CONCURRENT
#warning "Using Multi-Thread Shortest Path"
    res = multiThreadShortestPaths();
#else
#warning "Using Single-Thread Shortest Path"
    res = singleThreadShortestPaths();
#endif
#if defined(DEBUG_VELO) || defined(DEBUG_MISSING_PATHS)
    std::cerr << "Paths missing : " << notReachableRoutes << '/' << nbBicycleNodes*nbBicycleNodes-nbBicycleNodes << '\n';
#endif

    return res;
}

void AllShortestPaths::mergePaths(Paths& allPaths, Paths const& singlePath) {
    allPaths.insert(std::end(allPaths), std::begin(singlePath), std::end(singlePath));
#ifdef DEBUG_ONLY_PROCESSED_NODES
    std::cerr << ++processedNodes << " nodes processed" << '\n';
#endif
}

std::vector<Path> AllShortestPaths::singleShortestPaths(size_t const& n) {
    auto const& nodes = *pNodes;
    auto const& edges = *pEdges;

    std::vector<double> dist(nodes.size(), -1.);
    std::vector<size_t> prev(nodes.size());
    std::vector<bool> visited(nodes.size(), false);
    std::unordered_set<size_t> bicycleVisited;

    using QueueType = std::pair<size_t, double>;
    struct comparator {
        bool operator()(QueueType const& lhs, QueueType const& rhs) {
            return (lhs.second > rhs.second);
        }
    };
    std::priority_queue<QueueType, std::vector<QueueType>, comparator> queue;
    dist[n] = 0.;
    queue.push({n, 0.});
    while (!queue.empty() && bicycleVisited.size() < nbBicycleNodes) {
        auto next = queue.top();
        queue.pop();
        auto nextId = next.first;
        if (visited[nextId])
            continue;
        visited[nextId] = true;
        if (nodes[nextId].isBicycleParking)
            bicycleVisited.insert(nextId);

        for (auto const& neighbor: edges[nextId]) {
            auto neighborId = neighbor.first;
            if (dist[neighborId] == -1.
            || dist[neighborId] > dist[nextId] + neighbor.second) {
                prev[neighborId] = nextId;
                dist[neighborId] = dist[nextId] + neighbor.second; 
                queue.push({neighborId, dist[neighborId]});
            }
        }
    }

    std::vector<Path> res;
    res.reserve(nodes.size());
    for (auto const& node: bicycleNodes) {
        std::vector<size_t> completePath;
        if (dist[node] != -1. && node != n) {
            completePath.clear();
            auto t = node;
            while (1) {
                completePath.push_back(t);
                if (t == n) break;
                t = prev[t];
            }
            std::reverse(std::begin(completePath), std::end(completePath));
            Path newPath;
            newPath.src = n;
            newPath.dest = node;
            newPath.elems = completePath;
        }
#if defined(DEBUG_VELO) || defined(DEBUG_MISSING_PATHS)
        else if (node != n) {
            ++notReachableRoutes;
        }
#endif
    }
    return res;
}

// Multi-Thread Shortest Paths implementation
Paths AllShortestPaths::multiThreadShortestPaths() {
    auto&& mapFunction = singleShortestPaths;
    auto calculations = QtConcurrent::mapped(bicycleNodes, mapFunction);
    calculations.waitForFinished();

    size_t nbTotalPaths = 0;
    for (auto const& chunk: calculations)
        nbTotalPaths += chunk.size();

    Paths res;
    res.reserve(nbTotalPaths);
    for (auto const& chunk: calculations) {
        for (auto const& p: chunk) {
            res.push_back(p);
#ifdef DEBUG_VELO
            std::cerr << p.src << " -> " << p.dest << " = " << p.dist << " path = ";
            for (auto const& e: p.elems)
                std::cerr << e << ' ';
            std::cerr << '\n';
#endif
        }
    }
    return res;
}

// Mono-Thread Shortest Paths implementation
Paths AllShortestPaths::singleThreadShortestPaths() {
    Paths res;
    for (auto const& n: bicycleNodes) {
        auto path = singleShortestPaths(n);
        mergePaths(res, path);
    }
    return res;
}

// utility functions to pipe results
void printGraphAndShortestPaths(Nodes const& nodes, AdjacencyList const& edges, Paths const& paths) {
    printGraph(nodes, edges);
    std::cout << paths.size() << '\n';
    for (auto const& p: paths) {
        std::cout << p.src << ' ' << p.dest << ' ' << p.dist << ' ' << p.elems.size();
        for (auto const& e: p.elems)
            std::cout << ' ' << e;
        std::cout << '\n';
    }
}

std::tuple<Nodes, AdjacencyList, Paths> buildGraphAndPaths(QTextStream& in) {
    auto rawGraph = buildGraph(in);
    auto const& nodes = rawGraph.first;
    auto const& edges = rawGraph.second;
    size_t nbPaths;
    in >> nbPaths;
    
    Paths paths(nbPaths);
    for (size_t i = 0; i < nbPaths; ++i) {
        auto& p = paths[i];
        in >> p.src >> p.dest >> p.dist;
        size_t elemsSize;
        in >> elemsSize;
        p.elems.resize(elemsSize);
        for (auto& x: p.elems)
            in >> x;
    }

    return std::make_tuple(nodes, edges, paths);
}
} // end namespace osm
