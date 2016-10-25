#ifndef DAG_FLOODFILL_H
#define DAG_FLOODFILL_H
/** @class   DAG::FloodFill
 *
 *  @brief FloodFill creates blocks of connected elements
 *
 *   FLOODFILL uses the DAG BFSVisitor to find groups of connected nodes
 *
 *  Example usage:
 *
 *    typedef DAG::Node<long> PFNode;
 typedef std::unordered_map<long,PFNode> Nodes;
 Nodes myNodes;
 long id1, id2;
 id1=1;
 id2=2;
 DAG::FloodFill<long> FFill;
 myNodes.emplace(id1, PFNode(id1));
 myNodes.emplace(id2, PFNode(id2));
 myNodes[id1].addChild(myNodes[id2]);

 for (auto & nodevector : FFill.traverse(myNodes)) {
 std::cout << "Block: ";
 for (auto &node : nodevector) {
 std::cout<< node->value()<< ", " ;
 }
 }
 std::cout<< std::endl;

 *
 *
 *  @author  Alice Robson
 *  @date    2016-04-12
 */

#include "DirectedAcyclicGraph.h"
#include <map>

namespace DAG {
///FloodFill creates blocks of connected elements
template <typename T>  /// T is what goes inside of a Node eg a long Id
class FloodFill {

  typedef Node<T> TNode;
  typedef std::map<T, TNode> Nodemap;
  typedef std::unordered_set<const TNode*> Nodeset;
  typedef std::vector<const TNode*> Nodevector;

public:
  FloodFill();
  /// Return a vector that itself contains vectors of connected nodes
  std::vector<Nodevector> traverse(Nodemap&);

private:
  /// which nodes have been visited (reset each time a traversal is made)
  Nodeset m_visited;
};

template <typename T>
FloodFill<T>::FloodFill() {}

template <typename T>
std::vector<typename FloodFill<T>::Nodevector> FloodFill<T>::traverse(FloodFill<T>::Nodemap& nodes) {
  std::vector<Nodevector> resultsVector;

  m_visited.clear();
  BFSVisitor<TNode> bfs;

  for (auto& elem : nodes) {

    if (m_visited.find(&elem.second) != m_visited.end()) continue;  // already done this node so skip the rest

    // do a BFS search on any node that has not yet been visited
    Nodevector result = bfs.traverseUndirected(elem.second);
    for (const TNode* n : result)
      m_visited.insert(n);  // mark these as visited

    resultsVector.push_back(result);
  }
  return resultsVector;  // Move
}
}

#endif /* FloodFill_h */
