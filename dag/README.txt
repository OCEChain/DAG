
Supports traversal of a DirectedAcyclicGraph (also known here as DAG )
 implemented using a templated Node alongside a visitor algorithm
 
 Installation

download from github

mkdir build
cd build
cmake ..
make

For Xcode project use: cmake -G Xcode ..




Implementation details


Directed Acyclic Graph:
Nodes may have multiple children and /or multiple parents.
A search may be for children, parents or undirected links.
An undirected search finds all nodes that are connected to the start node(s).


New visiting algorithms can be created by the user by deriving from the Visitor class interface (BFSVisitor
is an example of this.)

The Node class is templated Node<T>
where T is intended to be either an identifier or the item of interest.
The Node class may not be const, but the thing it contains (T) may be set to be a const object

Nodes may contain 
	  - simple structures such as an int, long or pair
	  - with polymorphic classes ( T is set to &Base of the Base class)
	  - with Boost:Any  which allows direct insertion into the Nodes of any mixed set of class items
	    here T= const Boost::Any&

Example usage:
	  typedef DAG::Node<const int> INode;
	   INode n0(0);
	   INode n1(1);
	   INode n2(2);
	   // and now define the dag
	   n0.addChild(n1);  // link between n0 and n1
	   n0.addChild(n2);  // link between n0 and n2 etc
	
	   // Start at node 0
	  DAG::BFSVisitor<INode> bfs;
	  for (auto n : bfs.traverseChildren(n0)) {
	  int id = n->value();
	  std::cout << "Node: " << n->value()  << std::endl;
	  }

 Examples are provided for the following cases
 (i) Int identifier
 T is set to a const int identifier 

 (ii) T is a pair
 
(iii) Polymorphic classes
 T is set to be const &Base and the nodes include Base and Middle (derives from Base) instances.
 Note that &Base is used for T in order to avoid copying the classes and in order that polymorphism is available
 

