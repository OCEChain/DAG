//
//  Created by Alice Robson on 14/12/15.
//  Copyright © 2015 CERN. All rights reserved.
//

#include "dag/DirectedAcyclicGraph.h"


int main() {
  // Construct a DirectedAcyclic Graph DAG
  // In which the nodes are identifeid by a (unique) int w
  
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

  typedef DAG::Node<const int> INode;

  // create a set of nodes
  INode n0(0);
  INode n1(1);
  INode n2(2);
  INode n3(3);
  INode n4(4);
  INode n5(5);
  INode n6(6);
  INode n7(7);
  INode n8(8);

  // and now define the dag
  n0.addChild(n1);  // link between n0 and n1
  n0.addChild(n2);  // link between n0 and n2 etc
  n0.addChild(n3);
  n1.addChild(n4);
  n1.addChild(n5);
  n1.addChild(n6);
  n7.addChild(n8);
  n7.addChild(n4);
  n3.addChild(n6);

  // Start at node 0
  // Breath First Search uses an iterative method to traverse
  // output the Datatype of all children
  std::cout << std::endl << "TRAVERSE CHILDREN (start Node 0) " << std::endl;
  DAG::BFSVisitor<INode> bfs;
  for (auto n : bfs.traverseChildren(n0)) {
    int id = n->value();
    std::cout << "Node: " << id  << std::endl;
  }
  return 0;
}
