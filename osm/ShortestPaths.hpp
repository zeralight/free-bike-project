#ifndef SHORTEST_PATHS_HPP
#include <vector>
#include <unordered_map>
#include <map>
#include <tuple>

#include "OsmParser.hpp"

namespace osm {

/**
 * @ingroup osm
 * @This structure holds information about a shortest path between 2 points
 * Only the next hop from source to destination is stored for efficient memory management
 * @param src starting point
 * @param dest destination
 * @param dist distance between the points
 * @param nextHop the first intermediate point in the shortest path from src to dest
 */
struct Path {
    size_t src;
    size_t dest;
    double dist;
    size_t nextHop;
};
using Paths = std::vector<Path>;

/**
 * @ingroup osm
 * @brief this class implements the Dijkstra Algorithm on all the bicycle nodes
 * It can run it on a single thread or on multi threads
 * @warning While the multi-thread version runs fast, it uses a lot of memory than the other one !
 * by default, multithreading is enable, to use the other version, enable the macro QT_NO_CONCURRENT in the class implementation
 */
class AllShortestPaths {
    private:
        struct AlgoInput {
            Nodes nodes;
            AdjacencyList edges;
            size_t nbBicycleNodes;
        };
        static AdjacencyList const* pEdges;
        static Nodes const* pNodes;
        static std::vector<size_t> bicycleNodes;
        static size_t nbBicycleNodes;

        static Paths singleShortestPaths(size_t const& src);
        static void mergePaths(Paths& allPaths, Paths const& singlePath);
        static Paths singleThreadShortestPaths();
        static Paths multiThreadShortestPaths();
    public:
        /**
         * @brief the starting point of the algorithm
         * if you have concurrence enabled, the MapReduce implementation will be used.
         * @param nodes vector of nodes of the graph
         * @param adjList adjacency list of the graph
           @return list of paths describing shortests paths between every pair of bicycle parking nodes
         */
        static Paths run(Nodes const& nodes, AdjacencyList const& adjList);
};

// utility functions to pipe results between processes
/**
 * @ingroup osm
 * @brief output Graph and Shortests paths to standard output
 * There should be another process consuming these data for another use later
 * @param nodes nodes of the graph
 * @param edges adjacency list of the graph
 * @param paths list of paths describing the shortest paths
 */
void printGraphAndShortestPaths(osm::Nodes const& nodes, osm::AdjacencyList const& edges, osm::Paths const& paths);
/**
 * @ingroup osm
 * @brief consume text input to produce a graph with all shortests paths between bicycle parking nodes
 * @param input the text to consume
 * @return tuple containing the nodes, adjacency list and all paths
 */
std::tuple<Nodes, AdjacencyList, Paths> buildGraphAndPaths(QTextStream& input);

} // end namespace osm
#define SHORTEST_PATHS_HPP
#endif
