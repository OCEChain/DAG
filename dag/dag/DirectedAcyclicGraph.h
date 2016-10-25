//
//  DirectedAcyclicGraph.h
//
//
//  Created by Alice Robson on 14/12/15.
//  Copyright © 2015 CERN. All rights reserved.
//

/**
 * @file DirectedAcyclicGraph.h
 * @brief Implementation of Directed Acyclic Graph
 *
 * Supports traversal of a DirectedAcyclicGraph (also known here as DAG or a polytree)
 * implemented using a templated Node alongside algorithms to visit linked nodes
 *
 *  Directed Acyclic Graph:
 *  Nodes may have multiple children and /or multiple parents.
 *  A search may be for children, parents or undirected links.
 *  An undirected search finds all nodes that are connected to the start node(s).
 *
 *
 *  New visiting algorithms can be created by the user by deriving from the Visitor class interface (BFSVisitor
 *  is an example of this.)
 *
 *  The Node class is templated Node<T>
 *  where T is intended to be either an identifier or the item of interest.
 *  The Node class may not be const, but the thing it contains (T) may be set to be a const object
 * 
 *  Nodes may contain 
 *    - simple structures such as an int, long or pair
 *    - with polymorphic classes ( T is set to &Base of the Base class)
 *    - with Boost:Any  which allows direct insertion into the Nodes of any mixed set of class items
 *      here T= const Boost::Any&
 *  Example usage:
 *    typedef DAG::Node<const int> INode;
 *     INode n0(0);
 *     INode n1(1);
 *      INode n2(2);
 *   // and now define the dag
 *    n0.addChild(n1);  // link between n0 and n1
 *    n0.addChild(n2);  // link between n0 and n2 etc
 
 *    // Start at node 0
 *   DAG::BFSVisitor<INode> bfs;
 *    for (auto n : bfs.traverseChildren(n0)) {
 *    int id = n->value();
 *    std::cout << "Node: " << n->value()  << std::endl;
 *    }
 */

#ifndef DAG_DirectedAcyclicGraph_h
#define DAG_DirectedAcyclicGraph_h

#include <iostream>
#include <list>
#include <queue>
#include <unordered_set>

/// DirectedAcyclicGraph Namespace
namespace DAG {

// note internal use of pointer to N (supports the Nodes being concrete objects)
template <typename N>
using Nodeset = std::unordered_set<const N*>;  ///<allows find and just one of each node
template <typename N>
using Nodevector = std::vector<const N*>;  ///<typically used to return results

/// Visitor interface
/**Defines the visitor class interface for the DirectedAcyclicGraph
 */
/// Visitor Class/Interface templated on the Node N
template <typename N>  // N is the templated Node
class Visitor {
public:
  Visitor();  ///<Constructor
  /// Key function for visitor pattern
  virtual void visit(const N* node) = 0;
  /// returns vector of all child nodes (including the start node and all children of children)
  virtual const Nodevector<N>& traverseChildren(const N& startnode, int depth) = 0;
  /// returns vector of all parent nodes (including the start node and all parents of parents)
  virtual const Nodevector<N>& traverseParents(const N& startnode, int depth) = 0;
  /// returns everything linked to the start node
  virtual const Nodevector<N>& traverseUndirected(const N& startnode, int depth) = 0;

protected:
};

/// Node class for visitor pattern templated on T the item of interest
template <typename T>  // T is the item of interest inside the Node
class Node {
public:
  typedef Node<T> TNode;
  Node(const T& v);  ///< Constructor
  Node();            ///< Needed for putting a Node inside a unordered_set
  // ideally no copying because it means nodes are no longer unique
  TNode& operator=(TNode&) = delete;
  TNode& operator=(const TNode&) = delete;
  // unordered_set requires these to be available
  Node(TNode&) = default;
  Node(const TNode&) = default;
  // Move is good
  TNode& operator=(TNode&& other) = default;
  Node(TNode&& other) = default;

  void accept(Visitor<TNode>& visitor) const;  ///< Key function for visitor pattern
  void addChild(Node& node);  ///< Add in a link (this will set the reverse parent link in the other node)
  const T& value() const { return m_val; };  ///< return the node item
  const Nodeset<TNode>& children() const { return m_children; }
  const Nodeset<TNode>& parents() const { return m_parents; }

protected:
  T m_val;                                                 ///< thing that the node is encapsulating (eg identifier )
  Nodeset<TNode> m_children;                               ///< direct child nodes
  Nodeset<TNode> m_parents;                                ///< direct parent nodes
  void addParent(Node& node) { m_parents.insert(&node); }  // private as only available via addChild
};

template <typename N>  /// Breadth First Search implementation of BFSVisitor (iterative)
  class BFSVisitor : public Visitor<N> { ///N is the Node
public:
  BFSVisitor();
  void visit(const N* node) override;  ///< key to visitor pattern
  const Nodevector<N>& traverseChildren(const N& node, int depth = -1) override;
  const Nodevector<N>& traverseParents(const N& node, int depth = -1) override;
  const Nodevector<N>& traverseUndirected(const N& node, int depth = -1) override;

protected:
  Nodeset<N> m_visited;    ///< which nodes have been visited (reset each time a traversal is made)
  Nodevector<N> m_result;  ///< the list of nodes that are linked and that will be returned
  enum class enumVisitType { CHILDREN, PARENTS, UNDIRECTED };  ///< internal enumeration

  /// core traversal code uses by all of the public traversals
  virtual void traverse(const DAG::Nodeset<N>& nodes, BFSVisitor<N>::enumVisitType visittype,
                        int depth);  // the iterative method
  bool alreadyVisited(const N* node) const;
};

/// Breadth First Search alternative implementation using recursion
template <typename N>
class BFSRecurseVisitor : public BFSVisitor<N> {
public:
private:
  /// core traversal code uses by all of the public traversals
  virtual void traverse(const DAG::Nodeset<N>& nodes, typename BFSVisitor<N>::enumVisitType visittype,
                        int depth) override;
};

/// Constructor
template <typename T>
Node<T>::Node(const T& v) : m_val(v) {}

/// Constructor
template <typename T>
Node<T>::Node() : m_val(T()) {}

template <typename T>
void Node<T>::addChild(Node& node) {
  // AddChild automatically adds in the parent link - this should be a safer route and avoid
  // missing links
  m_children.insert(&node);
  node.addParent(*this);
}

/**
 accept the visitor
 @param Visitor<TNode>& visitor
 @return void
 */
template <typename T>
void Node<T>::accept(Visitor<TNode>& visitor) const {
  visitor.visit(this);
};

/// Constructor
template <typename N>
Visitor<N>::Visitor() {}

/// Constructor
template <typename N>
BFSVisitor<N>::BFSVisitor() : Visitor<N>(), m_visited() {}

/**
 visit a node - add the node to the results and mark as "visited"
 @param N* node - the node that is to be visited
 @return void
 */
template <typename N>
void BFSVisitor<N>::visit(const N* node) {
  m_result.push_back(node);  // add to result
  m_visited.insert(node);    // mark it as visited
}

template <typename N>
bool BFSVisitor<N>::alreadyVisited(const N* node) const {
  if (m_visited.find(node) == m_visited.end()) return false;
  return true;
}

/**
 traverse the nodes using Breadth First Search implemented using a Queue
 @param Nodeset& nodes - the start node(s)
 @param typename BFSVisitor<N>::enumVisitType visittype - CHILDREN/PARENTS/UNDIRECTED
 @param int depth - how many levels to visit (-1 = everything, 0 = start node(s), 2= start node plus 2 levels)
 @return void
 */
template <typename N>
void BFSVisitor<N>::traverse(const Nodeset<N>& nodes, typename BFSVisitor<N>::enumVisitType visittype, int depth) {
  typedef typename BFSVisitor<N>::enumVisitType pt;

  // Create a queue for the Breadth First Search
  std::queue<const N*> nodeQueue;
  std::queue<int> nodeDepth; //keeps track of the node depths so we can limit how deep we go if we wish

  // Mark the current node as visited and enqueue it
  for (auto const& node : nodes) {
    if (m_visited.find(node) == m_visited.end()) {  // if node is not listed as already being visited
      node->accept(*this);                          // mark as visited and add to results
      nodeQueue.push(node);                         // put into the queue
      nodeDepth.push(0);
    }
  }

  while (!nodeQueue.empty()) {

    // Get head Node from Queue and iterate its children and/or parents
    // each of the parents and children that are not already visited
    // get put onto the end of the queue
    // One this is done the head Node can be removed (popped)
    // from the queue and processing proceeds to the
    // next item in the queue
    int curdepth = nodeDepth.front();

    if ((depth < 0 || curdepth < depth) &&// NB depth=-1 means we are visiting everything
        ((visittype == pt::CHILDREN) | (visittype == pt::UNDIRECTED))) {  // use the children
      for (auto node : nodeQueue.front()->children()) {
        if (m_visited.find(node) == m_visited.end()) {  // check node is not already being visited
          node->accept(*this);

          nodeQueue.push(node);
          nodeDepth.push(curdepth + 1);
        }
      }
    }
    if ((depth < 0 || curdepth < depth) && //NB depth=-1 means we are visiting everything
        ((visittype == pt::PARENTS) | (visittype == pt::UNDIRECTED))) {  // use the parents
      for (auto node : nodeQueue.front()->parents()) {

        if (m_visited.find(node) == m_visited.end()) {  // check node is not already being visited
          node->accept(*this);

          nodeQueue.push(node);
          nodeDepth.push(curdepth + 1);
        }
      }
    }
    nodeQueue.pop();
    nodeDepth.pop();
  }
}

/**
 traverse the nodes using Breadth First Search implemented using a recursion
 @param Nodeset<N>& nodes - the start node(s)
 @param typename BFSVisitor<N>::enumVisitType visittype - CHILDREN/PARENTS/UNDIRECTED
 @param int depth - how many levels to visit (-1 = everything, 0 = start node(s), 2= start node plus 2 levels)
 @return void
 */
template <typename N>
void BFSRecurseVisitor<N>::traverse(const Nodeset<N>& nodes, typename BFSVisitor<N>::enumVisitType visittype,
                                    int depth) {
  // For a recursive  breadth first traversal we gather all nodes at the same depth
  typedef typename BFSVisitor<N>::enumVisitType pt;
  Nodeset<N> visitnextnodes;  // this collects all the nodes at the next "depth"

  if (nodes.empty()) {
    return;  // end of the recursion
  }

  for (auto node : nodes) {

    // Only process a node if not already visited
    if (BFSVisitor<N>::m_visited.find(node) == BFSVisitor<N>::m_visited.end()) {
      // this will add the node to the "result" and mark the node as visited
      node->accept(*this);

      // Now add in all the children/parent/undirected links for the next depth
      // and store these into visitnextnodes
      // NB depth=-1 means we are visiting everything
      if (depth != 0 && (visittype == pt::CHILDREN | visittype == pt::UNDIRECTED))
        for (const auto child : node->children()) {
          if (!this->alreadyVisited(child)) visitnextnodes.insert(child);
        }
      if (depth != 0 && (visittype == pt::PARENTS | visittype == pt::UNDIRECTED))
        for (const auto parent : node->parents()) {
          if (!this->alreadyVisited(parent)) visitnextnodes.insert(parent);
        }
    }
  }
  depth--;
  traverse(visitnextnodes, visittype, depth);
}

/**
 traverse the children using Breadth First Search
 @param N& startnode
 @param int depth - how many levels to visit (-1 = everything, 0 = start node(s), 2= start node plus 2 levels)
 @return const std::vector<N*>&  results vector of Nodes
 */
template <typename N>
const std::vector<const N*>& BFSVisitor<N>::traverseChildren(const N& startnode, int depth) {
  m_result = {};                // reset the list of results:
  Nodeset<N> root{&startnode};  // create an initial nodeset containing the root node
  traverse(root, BFSVisitor<N>::enumVisitType::CHILDREN, depth);
  m_visited = {};  // reset the list of visited nodes
  return m_result;
}

/**
 traverse the parents using Breadth First Search
 @param N& startnode
 @param int depth - how many levels to visit (-1 = everything, 0 = start node(s), 2= start node plus 2 levels)
 @return const std::vector<N*>&  results vector of Nodes
 */
template <typename N>
const std::vector<const N*>& BFSVisitor<N>::traverseParents(const N& startnode, int depth) {
  m_result = {};                // reset the list of results
  Nodeset<N> root{&startnode};  // create an initial nodeset containing the root node
  traverse(root, BFSVisitor<N>::enumVisitType::PARENTS, depth);
  m_visited = {};  // reset the list of visited nodes
  return m_result;
}

/**
 traverse all nodes linked to the start node using Breadth First Search
 @param N& startnode
 @param int depth - how many levels to visit (-1 = everything, 0 = start node(s), 2= start node plus 2 levels)
 @return const std::vector<N*>&  results vector of Nodes
 */
template <typename N>
const std::vector<const N*>& BFSVisitor<N>::traverseUndirected(const N& startnode, int depth) {
  m_result = {};                // reset the list of results
  Nodeset<N> root{&startnode};  // create an initial nodeset containing the root node
  traverse(root, BFSVisitor<N>::enumVisitType::UNDIRECTED, depth);
  m_visited = {};  // reset the list of visited nodes
  return m_result;
}
}

#endif /* DirectedAcyclicGraph */