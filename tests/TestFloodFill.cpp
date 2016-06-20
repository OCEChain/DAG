//
//  testFloodFill.cpp
//  fastsim
//
//  Created by Alice Robson on 15/04/16.
//
//
#include "gtest/gtest.h"
#include "directedacyclicgraph.h"
#include "FloodFill.h"
#include <unordered_map>


namespace papas {

TEST(floodfill, one) {
  typedef DAG::Node<long long> PFNode;
  typedef std::map<long long, PFNode> Nodes;
  
  Nodes myNodes;
  long long id1, id2;
  id1=1;
  id2=2;
  DAG::FloodFill<long long> FFill;
  myNodes.emplace(id1, PFNode(id1));
  myNodes.emplace(id2, PFNode(id2));
  myNodes[id1].addChild(myNodes[id2]);
  
  ASSERT_EQ(myNodes.at(id1).parents().size(),  0UL); //avoid compiler warning declare as unsigned long
  ASSERT_EQ(myNodes.at(id1).children().size(), 1UL);
  //ASSERT_EQ(myNodes.at(id1).children()[0],id2);
  
  for (const auto & nodevector : FFill.traverse(myNodes)) {
        ASSERT_EQ(nodevector.size(), 2UL);
    
  }
  
}

} // end namespace papas