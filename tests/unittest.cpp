// STL

#include <vector>
#include <algorithm>
#include "dag/DirectedAcyclicGraph.h"
#include "dag/FloodFill.h"
// catch
#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("DAG") {  /// ID test
  typedef DAG::Node<const int> INode;
  /*  Construct an example dag
   Here 0 and 8 are top level parents
   0 has children 1, 2, 3 etc
   
   
   //   8
   //    \
   //     \
   //      7
   //       \
   //        \
   //         4
   //        /
   //       /
   //      1--5
   //     / \
   //    /   \
   //   0--2  6
   //    \   /
   //     \ /
   //      3
   */

  
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
  
  // Start at node 0 search for children
  // Breath First Search uses an iterative method to traverse
  // output the Datatype of all children
  std::cout << std::endl << "TRAVERSE CHILDREN (start Node 0) " << std::endl;
  DAG::BFSVisitor<INode> bfs;
  auto bfsnodes = bfs.traverseChildren(n0);
  REQUIRE(bfsnodes.size() == 7);
  auto expected = std::vector<int>{0, 3, 2, 1, 6, 5, 4}; //can vary with multicores
  
  for (int i = 0; i<7 ;i++) {
    //std::cout <<bfsnodes[i]->value()<< expected[i]<<std::endl;
    REQUIRE(std::find(expected.begin(), expected.end(), bfsnodes[i]->value())!= expected.end());
  }
  
  // Start at node 0 search for all linked nodes
  bfsnodes = bfs.traverseUndirected(n0);
  expected = std::vector<int>{0, 3, 2, 1, 6, 5, 4, 7, 8}; //can vary with multicores
  REQUIRE(bfsnodes.size() == 9);

  for (int i = 0; i<9 ;i++) {
    //std::cout <<bfsnodes[i]->value()<< expected[i]<<std::endl;
    REQUIRE(std::find(expected.begin(), expected.end(), bfsnodes[i]->value())!= expected.end());
  }
}


TEST_CASE("FloodFill") {
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
  
  REQUIRE(myNodes.at(id1).parents().size()==0);
  REQUIRE(myNodes.at(id1).children().size()==1);

  for (const auto & nodevector : FFill.traverse(myNodes)) {
    REQUIRE(nodevector.size()==2);
    
  }
  
}


