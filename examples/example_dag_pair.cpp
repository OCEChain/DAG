#include "DirectedAcyclicGraph.h"

class idpair {
public:
  int itype;
  int ivalue;
  idpair(int t, int v) {
    itype = t;
    ivalue = v;
  };
};

int main() {

  typedef DAG::Node<const idpair> INode;

  // create a set of nodes
  // the nodes will be kept track of in the Node children and parent collections so
  // shared_ptr is used.
  INode n0(idpair(0, 2));
  INode n1(idpair(1, 3));
  INode n2(idpair(2, 3));
  INode n3(idpair(3, 2));
  INode n4(idpair(4, 2));
  INode n5(idpair(5, 2));
  INode n6(idpair(6, 2));
  // and now define the polytree
  // add the directed (parent -> child) branches of the polytree
  // each link requires an addChild and an addParent
  n0.addChild(n1);  // link between n0 and n1
  n1.addChild(n2);  // link between n0 and n2 etc
  n1.addChild(n3);
  n3.addChild(n6);
  n3.addChild(n4);
  n4.addChild(n5);
  n5.addChild(n6);

  DAG::BFSRecurseVisitor<INode> bfs;
  // Start at node 0 for the following examples

  // Example 1
  // BFSVisitor uses an iterative method to traverse
  // output the Datatype of all children
  std::cout << std::endl << "TRAVERSE CHILDREN (start Node 0)  1 level" << std::endl;
  for (auto n : bfs.traverseChildren(n0, 1)) {
    std::cout << n->value().itype << ":" << n->value().ivalue << std::endl;
  }
  
  std::cout << std::endl << "TRAVERSE UNDIRECTED (start Node 5) 2 levels " << std::endl;
  for (auto n : bfs.traverseUndirected(n5, 2)) {
    std::cout << n->value().itype << ":" << n->value().ivalue << std::endl;
  }
  
  std::cout << std::endl << "TRAVERSE CHILDREN (start Node 0)  all levels" << std::endl;

  for (auto n : bfs.traverseChildren(n0)) {
    std::cout << n->value().itype << ":" << n->value().ivalue << std::endl;
  }

  return 0;
}