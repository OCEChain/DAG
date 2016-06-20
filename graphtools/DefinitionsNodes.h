//
//  DefinitionsNodes.h
//  papas
//
//  Created by Alice Robson on 12/05/16.
//
//

#ifndef DefinitionsNodes_h
#define DefinitionsNodes_h

#include <map>
#include <vector>
#include "directedacyclicgraph.h"
#include "Id.h"
namespace papas {

typedef DAG::Node<Id::Type> PFNode;
typedef std::map<Id::Type, PFNode> Nodes;
extern Nodes emptyNodes; //TODO check
extern const Nodes emptyconstNodes; //TODO check

} // end namespace papas

#endif /* DefinitionsNodes_h */
