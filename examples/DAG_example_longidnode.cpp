//
//  template_tree.cpp
//  polytree
//
//  Created by Alice Robson on 14/12/15.
//  Copyright © 2015 CERN. All rights reserved.
//

//#include <algorithm>
#include "directedacyclicgraph.h"
#include "simpleidentifier.h"

long makeMergedClusterId() { return Id::makeId(enumDataType::CLUSTER, enumSubType::MERGED); }

long makeTrackid() { return Id::makeId(enumDataType::TRACK, enumSubType::RAW); }

int main() {
  // Construct a DirectedAcyclic Graph DAG
  // In which the nodes are identifeid by a (unique) long which
  // has been created vis the Id class and thus allows the user to check
  // various details of the associated object eg CLUSTER vs PARTICLE vs TRACK or ECAL vs HCAL etc
  // The details of these can be adjusted by creating a custom Id class

  /*  Construct an example polytree
   Here 0 and 8 are top level parents
   0 has children 1, 2, 3 etc


   ///   8
   ///    \
   ///     \
   ///      7
   ///       \
   ///        \
   ///         4
   ///        /
   ///       /
   ///      1--5
   ///     / \
   ///    /   \
   ///   0--2  6
   ///    \   /
   ///     \ /
   ///      3
   */

  // Now wrap each of these objects up into a Node and provide a label for each Node
  // Label is a template parameter so need not be a string

  typedef DAG::Node<const long> INode;

  // create a set of nodes
  // the nodes will be kept track of in the Node children and parent collections so
  // shared_ptr is used.
  INode n0(makeTrackid());
  INode n1(makeTrackid());
  INode n2(makeTrackid());
  INode n3(makeMergedClusterId());
  INode n4(makeMergedClusterId());
  INode n5(makeMergedClusterId());
  INode n6(makeTrackid());
  INode n7(makeTrackid());
  INode n8(makeTrackid());

  // and now define the polytree
  // add the directed (parent -> child) branches of the polytree
  // each link requires an addChild and an addParent
  n0.addChild(n1);  // link between n0 and n1
  n0.addChild(n2);  // link between n0 and n2 etc
  n0.addChild(n3);
  n1.addChild(n4);
  n1.addChild(n5);
  n1.addChild(n6);
  n7.addChild(n8);
  n7.addChild(n4);
  n3.addChild(n6);

  // Start at node 0 for the following examples

  // Example 1
  // BFSVisitor uses an iterative method to traverse
  // output the Datatype of all children
  std::cout << std::endl << "TRAVERSE CHILDREN (start Node 0) " << std::endl;
  std::cout << "Node : Nodetype" << std::endl;
  DAG::BFSVisitor<INode> bfs;
  for (auto n : bfs.traverseChildren(n0)) {
    long id = Id::uniqueId(n->value());
    if (Id::dataType(n->value()) == enumDataType::CLUSTER)
      std::cout << id - 1 << " :CLUSTER" << std::endl;  // subtract 1 to match the node number
    else if (Id::dataType(n->value()) == enumDataType::TRACK)
      std::cout << id - 1 << " :TRACK" << std::endl;  // subtract 1 to match the node number
  }

  // Example 2
  // Find all the nodes connected (undirected) with node 0
  // output their ids and whether they are leaf or root in the graph
  std::cout << std::endl << "TRAVERSE UNDIRECTED (start Node 0)  " << std::endl;
  std::cout << "Node : LEAF/ROOT" << std::endl;
  for (auto n : bfs.traverseUndirected(n0)) {
    std::cout << Id::uniqueId(n->value()) - 1;  // subtract 1 to match the node number
    if (n->children().size() == 0)
      std::cout << " LEAF";
    else if (n->parents().size() == 0)
      std::cout << " ROOT";
    std::cout << std::endl;
  }

  // Example 3
  // This is a recursive version which only outputs leaf nodes
  std::cout << std::endl << "TRAVERSE LEAF CHILDREN (RECURSIVE)   " << std::endl;
  std::cout << "Node" << std::endl;
  DAG::BFSRecurseVisitor<INode> bfsrecursive;
  for (auto n : bfs.traverseUndirected(n0)) {
    if (n->children().size() == 0)  // isLeaf
      std::cout << Id::uniqueId(n->value()) - 1 << std::endl;
  }
  return 0;
}