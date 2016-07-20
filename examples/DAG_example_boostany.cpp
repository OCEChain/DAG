//
//  DAG_exaple_boostany.cc
//
//
//  Created by Alice Robson on 14/12/15.
//  Copyright © 2015 CERN. All rights reserved.
//
#include "DirectedAcyclicGraph.h"
#include <boost/any.hpp>
#include <boost/type_index.hpp>

// This DAG example illustrates how to insert dissimilar items into a DAG.
// The boost::any class is used to wrap each item
// In the example below the boost:any contain a mix of integer and of class Middle.
// To recuperate the original item, the boost::any_cast must be used.

class Middle {  // example class
public:
  Middle(int i) : m_val(i){};
  void Write() const { std::cout << "middle: " + std::to_string(m_val) << std::endl; };
  int m_val;
};

int main() {
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

  typedef DAG::Node<boost::any> ANode;

  // Create some things to go inside the nodes
  // wrapping them into a boost::any
  boost::any ma0(0);          // an integer inside a boost::any
  boost::any ma1(Middle(1));  // class Middle inside a boost::any
  boost::any ma2(Middle(2));
  boost::any ma3(Middle(3));
  boost::any ma4(Middle(4));
  boost::any ma5(Middle(5));
  boost::any ma6(Middle(6));
  boost::any ma7(Middle(7));
  boost::any ma8(8);  // an integer inside a boost::any

  // Now wrap each of these objects up into a Node and provide a label for each Node
  ANode n0(ma0);
  ANode n1(ma1);
  ANode n2(ma2);
  ANode n3(ma3);
  ANode n4(ma4);
  ANode n5(ma5);
  ANode n6(ma6);
  ANode n7(ma7);
  ANode n8(ma8);

  // and now define the polytree
  // add the directed (parent -> child) branches of the polytree
  // each link requires an addChild and an addParent
  n0.addChild(n1);
  n0.addChild(n2);
  n0.addChild(n3);
  n1.addChild(n4);
  n1.addChild(n5);
  n1.addChild(n6);
  n7.addChild(n8);
  n7.addChild(n4);
  n3.addChild(n6);

  // choose a BFS visitor
  DAG::BFSVisitor<ANode> bfs;

  std::cout << std::endl;
  std::cout << "BOOST TRAVERSE UNDIRECTED (starting from 0)  " << std::endl;

  // unravel the results start from node 0
  for (auto n : bfs.traverseUndirected(n0)) {
    // check the boost::any type to see if it is an int or a middle
    // once the type is identified can cast to the appropriate type
    // and then use it as required
    if (n->value().type() == typeid(int)) {
      std::cout << "Integer: " << boost::any_cast<int>(n->value()) << std::endl;
    }
    if (n->value().type() == typeid(Middle)) {
      boost::any_cast<Middle>(n->value()).Write();
    }
  }

  std::cout << "END" << std::endl;
  return 0;
}
