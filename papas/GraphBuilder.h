#ifndef RECONSTRUCTION_GRAPHBUILDER_H
#define RECONSTRUCTION_GRAPHBUILDER_H

#include "DefinitionsCollections.h"
#include "DefinitionsNodes.h"

namespace papas {

class PFEvent;

/** @class   rec::GraphBuilder Reconstruction/Reconstruction/GraphBuilder.h GraphBuilder.h
 *
 * GraphBuilder takes a vector of identifiers and an unordered map of associated edges which have distance and link info
 * It uses the distances/links between elements to construct a set of connected blocks
 * Each element will end up in one (and only one) block
 * Blocks retain information of the elements and the distances between elements
 * The blocks can be used for future particle reconstruction
 * The ids must be unique and are expected to come from the Id class


 Usage example:

 GraphBuilder builder {ids, edges, history_nodes, pfevent};
 for (b in builder.blocks()) {
 ...
 }
 *
 *  @author  Alice Robson
 *  @date    2016-04-06
 */

class GraphBuilder {
public:
  /** Constructor

   * @param[in] ids : vector of unique identifiers eg of tracks, clusters etc
   * @param[in] edges : unordered_map of edges which contains all edges between the ids (and maybe more)
   *            an edge records the distance and links between two ids
   */
  GraphBuilder(Ids ids, Edges& edges);
  GraphBuilder& operator=(const GraphBuilder&);
  /// TODO add comment re arguments below what is Ids
  const std::vector<Ids> subGraphs() const {
    return m_subGraphs;
  };  ///<return the vector of Ids of the resulting subgraphs;
protected:
  void sortIds(Ids& ids);  ///<sorted by energy
  Edges& m_edges;
  std::vector<Ids> m_subGraphs;  ///< vector of subgraphs made by graphbuilder
private:
  Ids m_elementIds;    ///<uniqueids to be grouped into subgraphs
  Nodes m_localNodes;  ///<local nodes used in building subgraphs
};
}  // end namespace papas
#endif /* GraphBuilder_h */
