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
 * @param elems vector of nodes defining the path
 */
struct Path {
    size_t src;
    size_t dest;
    double dist;
    std::vector<size_t> elems;
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
        Nodes const& nodes;
        AdjacencyList const& edges;
        std::vector<size_t> bicycleNodes;
        size_t nbBicycleNodes;

        void mergePaths(Paths& allPaths, Paths const& singlePath);
        Paths singleThreadShortestPaths();
        Paths multiThreadShortestPaths();
    public:
       
        /**
         * @brief initialize the algorithm parameters
         * @param nds list of nodes of the graph
         * @param l adjacency list of the graph
         */ 
        AllShortestPaths(Nodes const& nds, AdjacencyList const& l);
        
        /**
         * @brief the starting point of the algorithm
         * if you have concurrence enabled, the MapReduce implementation will be used.
           @return list of paths describing shortests paths between every pair of bicycle parking nodes
         */
        Paths run();
        
        /**
        * @brief Shortest path on a single node
        * It is required by Qt to be an operator()
        * @param source the source point of the Shortest Path algorithm
        * @return list of paths describing the shortest path from source to the other bicycle parkings
        */
        Paths operator()(size_t const& source) const;
        
        /**
         * @brief A mandatory alias by Qt when using QtConcurrent::mapped
         */
        using result_type = Paths;
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
