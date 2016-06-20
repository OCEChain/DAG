//  template_tree.cpp
//  polytree
//
//  Created by Alice Robson on 14/12/15.
//  Copyright © 2015 CERN. All rights reserved.
//


#include <algorithm>
#include <iostream>
#include "directedacyclicgraph.h"





//Example base classs
class Base {
public:
   Base(int i): m_val(i) {};
   virtual void Write() const { std::cout << "base: " + std::to_string(m_val) << std::endl;};
   int m_val;
};

//Example derived class
class Middle: public Base {
public:
   using Base::Base;
   void Write() const override ;
};

void Middle::Write() const { std::cout << "middle: " + std::to_string(m_val) << std::endl;};



int main()
{
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

   // Create some things to go inside each of the 9 nodes
   // Here they are all derived from Base
   Base b0(0);
   Middle m1(1);
   Middle m2(2);
   Middle m3(3);
   Middle m4(4);
   Middle m5(5);
   Middle m6(6);
   Middle m7(7);
   Base b8(8);

   //Now wrap each of these objects up into a Node
   typedef DAG::Node<const Base& > BNode;
   BNode   n0(b0);
   BNode   n1(m1);
   BNode   n2(m2);
   BNode   n3(m3);
   BNode   n4(m4);
   BNode   n5(m5);
   BNode   n6(m6);
   BNode   n7(m7);
   BNode   n8(b8);

   // and now define the polytree
   // add the directed (parent -> child) branches of the polytree
   n0.addChild(n1);
   n0.addChild(n2);
   n0.addChild(n3);
   n1.addChild(n4);
   n1.addChild(n5);
   n1.addChild(n6);
   n7.addChild(n8);
   n7.addChild(n4);
   n3.addChild(n6);
   
   //USE NODE 0 AS THE START NODE

   //BFSVisitor uses an iterative method to traverse
   DAG::BFSVisitor<BNode> bfs;

   std::cout << std::endl << "TRAVERSE  LEAF CHILDREN (starting from 0)  " <<
             std::endl;
   for (auto y : bfs.traverseChildren(n0)) {
      if (y->children().size() == 0)
         y->value().Write();
   }

   //Find all the nodes connected (undirected) with node 0
   std::cout << std::endl << "POLYMORPHIC TRAVERSE UNDIRECTED (starting from 0)  "
             << std::endl;
   for (const auto& n : bfs.traverseUndirected(n0))
      n->value().Write();

   return 0;
}




