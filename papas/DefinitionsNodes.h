//
//  DefinitionsNodes.h
//  papas
//
//  Created by Alice Robson on 12/05/16.
//
//

#ifndef DefinitionsNodes_h
#define DefinitionsNodes_h

#include "Id.h"
#include "DirectedAcyclicGraph.h"
#include <map>
#include <vector>
namespace papas {

typedef DAG::Node<Id::Type> PFNode;
typedef std::map<Id::Type, PFNode> Nodes;

}  // end namespace papas

#endif /* DefinitionsNodes_h */
