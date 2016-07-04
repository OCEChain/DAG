//
//  directedacyclicgraph.h
//
//
//  Created by Alice Robson on 14/12/15.
//  Copyright © 2015 CERN. All rights reserved.
//

/**
 * @file directedacyclicgraph.h
 * @brief Implementation of Directed Acyclic Graph
 *
 * Supports traversal of a DirectedAcyclicGraph (also know here as DAG or a polytree)
 * implemented using a templated Node alongside alogorithms to visit linked nodes
 *
 *  Directed Acyclic Graph:
 *  Nodes may have multiple children and /or multiple parents.
 *  A search may be for children, parents or undirected links.
 *  An undirected search finds all nodes that are connected to the start node(s).
 *
 *  Visitor Pattern:
 *  The visitor pattern is nicely described on WIKI https://en.wikipedia.org/wiki/Visitor_pattern
 *
 *  The key things are that the Node class (or Element) class has an Accept function which calls the
 *  Visitor class visit function.
 *  This structuring allows for possible double dispatch ie polymorphism for both
 *  the node and the visitor class. It also allows the visitor class to work cleanly
 *  without interference in the Node class.
 *  New visitor patterns can be created by the user by deriving from the Visitor class interface (BFSVisitor
 *  is an example of this.
 *
 *  The Node class is templated Node<T>
 *  where T is intended to be either an identifier or the item of interest.
 *  The Node class may not be const, but the think it contains (T) may be set to be a const object
 *
 *  Examples are provided for the following cases
 *  (i) Long identifier
 *  T is set to a const long identifier which contains encoding information about the items of interest.
 *  The actual item of interest is not contained within nodes and therefore a separate set of collection structures
 *  such as unordered_maps will be required to link between the long identifier and the various collections
 *  For example if the nodes were either tracks or clusters then
 *  we need:- stl::unordered_map<id,cluster>
 *  stl::unordered_map<id,track>
 *  And the user must generate a unique id for each cluster and track
 *  The identifier class provides an example of the encoding and decoding of node information
 *
 *  (ii) Polymorphic classes
 *  T is set to be const &Base and the nodes include Base and Middle (derives from Base) instances.
 *  Note that &Base is used for T in order to avoid copying the classes and in order that polymorphism is available
 *
 * (iii) Boost:Any
 *  Allows direct insertion into the Nodes of any mixed set of class items
 *  T= const Boost::Any&
 *
 */

#ifndef DirectedAcyclicGraph_h
#define DirectedAcyclicGraph_h

#include <iostream>
//#include <unordered_set>
#include <list>
#include <queue>
#include <set>

/// DirectedAcyclicGraph Namespace
namespace DAG {

/// Visitor interface
/**Defines the visitor class interface for the DirectedAcyclicGraph
 */
/// Visitor Class/Interface templated on the Node N
template <typename N>  // N is the templated Node
class Visitor {
public:
  typedef std::set<const N*> Nodeset;        ///<allows find and just one of each node - used for traversals
  typedef std::vector<const N*> Nodevector;  ///<used to return results
  Visitor();                                 ///<Constructor
  /// Key function for visitor pattern
  virtual void visit(const N* node) = 0;
  /// returns vector of all child nodes (including the start node and all children of children)
  virtual const Nodevector& traverseChildren(const N& startnode) = 0;
  /// returns vector of all parent nodes (including the start node and all parents of parents)
  virtual const Nodevector& traverseParents(const N& startnode) = 0;
  /// returns everything linked to the start node
  virtual const Nodevector& traverseUndirected(const N& startnode) = 0;

protected:
};

/// Node class for visitor pattern templated on T the item of interest
template <typename T>  // T is the item of interest inside the Node
class Node {
public:
  typedef Node<T> TNode;
  typedef std::set<Node*> Nodeset;  // Allows find with no repeat nodes
  /// Constructor
  Node(T v);
  /// Needed for putting a Node inside a unordered_map
  Node();
  // ideally no copying because it means nodes are no longer unique
  TNode& operator=(TNode&) = delete;
  TNode& operator=(const TNode&) = delete;
  // However, unordered_map requires these to be available
  // TODO make this more formal
  Node(TNode&) { std::cout << "Unexpected Node copy"; };
  Node(const TNode&) { std::cout << "Unexpected Node copy ="; };
  // Move is good
  TNode& operator=(TNode&& other) = default;
  Node(TNode&& other) = default;

  /// Key function for visitor pattern
  void accept(Visitor<TNode>& visitor) const;
  /// Add in a link (this will set the reverse parent link in the other node)
  void addChild(Node& node);
  /// return the node item
  const T& value() const { return m_val; };
  const Nodeset& children() const { return m_children; }
  const Nodeset& parents() const { return m_parents; }

protected:
  T m_val;                                                 ///< thing that the node is encapsulating (eg identifier )
  Nodeset m_children;                                      ///< direct child nodes
  Nodeset m_parents;                                       ///< direct parent nodes
  void addParent(Node& node) { m_parents.insert(&node); }  // private as only available via addChild
};

// Breadth First Search implementation of BFSVisitor (iterative)
template <typename N>  /// N is the Node
class BFSVisitor : public Visitor<N> {
public:
  /// used for traversals
  typedef std::set<const N*> Nodeset;  // internal use of pointer (supports the Nodes being concrete objects)
  /// used for returning results
  typedef std::vector<const N*> Nodevector;

  BFSVisitor();
  void visit(const N* node) override;  ///< key to visitor pattern

  const Nodevector& traverseChildren(const N& node) override;
  const Nodevector& traverseParents(const N& node) override;
  const Nodevector& traverseUndirected(const N& node) override;
  bool alreadyVisited(N* node) const;

protected:
  /// which nodes have been visited (reset each time a traversal is made)
  Nodeset m_visited;
  /// the list of nodes that are linked and that will be returned
  Nodevector m_result;
  /// internal enumeration
  enum class enumVisitType { CHILDREN, PARENTS, UNDIRECTED };
  /// core traversal code uses by all of the public traversals
  virtual void traverse(const Nodeset& nodes, BFSVisitor<N>::enumVisitType visittype);  // the iterative method
};

/// Breadth First Search alternative implementation using recursion
template <typename N>
class BFSRecurseVisitor : public BFSVisitor<N> {
public:
private:
  /// core traversal code uses by all of the public traversals
  virtual void traverse(const typename BFSVisitor<N>::Nodeset& nodes,
                        typename BFSVisitor<N>::enumVisitType visittype) override;
};

/// Constructor
template <typename T>
Node<T>::Node(T v) : m_val(v) {}

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
bool BFSVisitor<N>::alreadyVisited(N* node) const {
  if (m_visited.find(node) == m_visited.end()) return false;
  return true;
}

/**
 traverse the nodes using Breadth First Search implemented using a Queue
 @param Nodeset& nodes - the start node(s)
 @param typename BFSVisitor<N>::enumVisitType visittype - CHILDREN/PARENTS/UNDIRECTED
 @return void
 */
template <typename N>
void BFSVisitor<N>::traverse(const Nodeset& nodes, typename BFSVisitor<N>::enumVisitType visittype) {
  typedef typename BFSVisitor<N>::enumVisitType pt;

  // Create a queue for the Breadth First Search
  std::queue<const N*> nodeQueue;

  // Mark the current node as visited and enqueue it
  for (auto const& node : nodes) {
    if (m_visited.find(node) == m_visited.end()) {  // if node is not listed as already being visited
      node->accept(*this);                          // mark as visited and add to results
      nodeQueue.push(node);                         // put into the queue
    }
  }

  while (!nodeQueue.empty()) {

    // Get head Node from Queue and iterate its children and/or parents
    // each of the parents and children that are not already visited
    // get put onto the end of the queue
    // One this is done the head Node can be removed (popped)
    // from the queue and processing proceeds to the
    // next item in the queue
    if ((visittype == pt::CHILDREN) | (visittype == pt::UNDIRECTED)) {  // use the children
      for (auto node : nodeQueue.front()->children()) {
        if (m_visited.find(node) == m_visited.end()) {  // check node is not already being visited
          node->accept(*this);
          nodeQueue.push(node);
        }
      }
    }
    if ((visittype == pt::PARENTS) | (visittype == pt::UNDIRECTED)) {  // use the parents
      for (auto node : nodeQueue.front()->parents()) {
        if (m_visited.find(node) == m_visited.end()) {  // check node is not already being visited
          node->accept(*this);
          nodeQueue.push(node);
        }
      }
    }
    nodeQueue.pop();
  }
}

/**
 traverse the nodes using Breadth First Search implemented using a recursion
 @param Nodeset& nodes - the start node(s)
 @param typename BFSVisitor<N>::enumVisitType visittype - CHILDREN/PARENTS/UNDIRECTED
 @return void
 */
template <typename N>
void BFSRecurseVisitor<N>::traverse(const typename BFSVisitor<N>::Nodeset& nodes,
                                    typename BFSVisitor<N>::enumVisitType visittype) {
  // For a recursive  breadth first traversal we gather all nodes at the same depth
  typedef typename BFSVisitor<N>::enumVisitType pt;
  typename BFSVisitor<N>::Nodeset visitnextnodes;  // this collects all the nodes at the next "depth"

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
      if (visittype == pt::CHILDREN | visittype == pt::UNDIRECTED)
        for (const auto child : node->children()) {
          if (!this->alreadyVisited(child)) visitnextnodes.insert(child);
        }
      if (visittype == pt::PARENTS | visittype == pt::UNDIRECTED)
        for (const auto parent : node->parents()) {
          if (!this->alreadyVisited(parent)) visitnextnodes.insert(parent);
        }
    }
  }
  traverse(visitnextnodes, visittype);
}

/**
 traverse the children using Breadth First Search
 @param N& startnode
 @return const std::vector<N*>&  results vector of Nodes
 */
template <typename N>
const std::vector<const N*>& BFSVisitor<N>::traverseChildren(const N& startnode) {
  m_result = {};             // reset the list of results:
  Nodeset root{&startnode};  // create an initial nodeset containing the root node
  traverse(root, BFSVisitor<N>::enumVisitType::CHILDREN);
  m_visited = {};  // reset the list of visited nodes
  return m_result;
}

/**
 traverse the parents using Breadth First Search
 @param N& startnode
 @return const std::vector<N*>&  results vector of Nodes
 */
template <typename N>
const std::vector<const N*>& BFSVisitor<N>::traverseParents(const N& startnode) {
  m_result = {};             // reset the list of results
  Nodeset root{&startnode};  // create an initial nodeset containing the root node
  traverse(root, BFSVisitor<N>::enumVisitType::PARENTS);
  m_visited = {};  // reset the list of visited nodes
  return m_result;
}

/**
 traverse all nodes linked to the start node using Breadth First Search
 @param N& startnode
 @return const std::vector<N*>&  results vector of Nodes
 */
template <typename N>
const std::vector<const N*>& BFSVisitor<N>::traverseUndirected(const N& startnode) {
  m_result = {};             // reset the list of results
  Nodeset root{&startnode};  // create an initial nodeset containing the root node
  traverse(root, BFSVisitor<N>::enumVisitType::UNDIRECTED);
  m_visited = {};  // reset the list of visited nodes
  return m_result;
}
}

#endif /* DirectedAcyclicGraph */
