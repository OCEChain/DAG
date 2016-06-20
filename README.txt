
Supports traversal of a DirectedAcyclicGraph (also know here as DAG or a polytree)
 implemented using a templated Node alongside a visitor pattern
 
 Installation

download from github

mkdir build
cd build
cmake ..
make

For Xcode project use: cmake -G Xcode ..

The make file will produce 2 executables
DAG_id - Nodes using long with encoded information
DAG_poly - polymorphic exampe

If Boost is installed and the BOOST_ROOT env value is set then a 3rd executable will also be built
DAG_any.



Implementation details


 Directed Acyclic Graph:
 Nodes may have multiple children and /or multiple parents.
 A search may be for children, parents or undirected links.
 An undirected search finds all nodes that are connected to the start node(s).
 
 Visitor Pattern:
 The visitor pattern is nicely described on WIKI https://en.wikipedia.org/wiki/Visitor_pattern
 
 The key things are that the Node class (or Element) class has an Accept function which calls the
 Visitor class visit function.
 This structuring allows for possible double dispatch ie polymorphism for both
 the node and the visitor class. It also allows the visitor class to work cleanly
 without interference in the Node class.
 New visitor patterns can be created by the user by deriving from the Visitor class interface (BFSVisitor
 is an example of this.
 
 The Node class is templated Node<T>
 where T is intended to be either an identifier or the item of interest.
 The Node class may not be const, but the think it contains (T) may be set to be a const object
 
 Examples are provided for the following cases
 (i) Long identifier
 T is set to a const long identifier which contains encoding information about the items of interest.
 The actual item of interest is not contained within nodes and therefore a separate set of collection structures
 such as unordered_maps will be required to link between the long identifier and the various collections
 For example if the nodes were either tracks or clusters then
 we need:- stl::unordered_map<id,cluster>
 stl::unordered_map<id,track>
 And the user must generate a unique id for each cluster and track
 The identifier class provides an example of the encoding and decoding of node information
 
 (ii) Polymorphic classes
 T is set to be const &Base and the nodes include Base and Middle (derives from Base) instances.
 Note that &Base is used for T in order to avoid copying the classes and in order that polymorphism is available
 
 (iii) Boost:Any
 Allows direct insertion into the Nodes of any mixed set of class items
 T= const Boost::Any&
