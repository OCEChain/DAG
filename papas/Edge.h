#ifndef RECONSTRUCTION_EDGE_H
#define RECONSTRUCTION_EDGE_H

#include "Id.h"
#include <iostream>

/** @class   rec::Edge Reconstruction/Reconstruction/Edge.h Edge.h
 *
 *  @brief An Edge stores end node ids, distance between the nodes, and whether they are linked
 *
 *  Example usage: Edge e = Edge(obj1.unqiueid, obj2.uniqueid, True, 0.0);
 *
 *  @author  Alice Robson
 *  @date    2016-04-05
 */

namespace papas {

class Edge {
public:
  /** @enum foo::EdgeType
   *  enumeration to describe the type of edge eg an hcal to hcal edge is type kHcalHcal
   */
  enum class EdgeType { kUnknown = 0, kEcalHcal, kEcalEcal, kEcalTrack, kHcalTrack, kHcalHcal, kTrackTrack };
  typedef uint64_t EdgeKey;

  Edge() : m_id1(0), m_id2(0), m_isLinked(false), m_distance(0){};
  /**
   *   @brief  Edge constructor - note that the ordering of id1 and id2 does not matter
   *
   *   @param[in]  id1 : element uniqueid enerated from Id class for one end
   *   @param[in]  id2 : element2 uniqueid generated from Id class for other end
   *   @param[in]  isLinked : boolean T/F
   *   @param[in]  distance: distance between two elements
   */
  Edge(Id::Type id1, Id::Type id2, bool isLinked, double distance);
  Edge(const Edge&) = default; //{std::cout <<"copy Edge";};
  Edge(Edge&&) = default;                        
  Edge& operator=(const Edge& other) = default;// {   std::cout<<"copy EDGE =";};
  Edge& operator=(Edge&& other) = default; // { std::cout <<"move edge =";};
  ~Edge() = default;

  Id::Type id1() const { return m_id1; }
  Id::Type id2() const { return m_id2; }
  bool isLinked() const { return m_isLinked; }  ///<boolean to mark if this edge links the two elements
  void setLinked(bool link) { m_isLinked = link; };
  double distance() const { return m_distance; }  ///<distance between the two elements
  Edge::EdgeKey key() const { return m_key; }  ///<unique key for this edge that can be found from the two element ids
  EdgeType edgeType() const { return m_edgeType; }  ///<describes what types of elements are connected
  Id::Type otherid(Id::Type id) const;  /// return the id of the other end, or -1 if id is not part of this edge
  friend std::ostream& operator<<(std::ostream& os, const Edge& egde);
  /**
    *   @brief  Static function that creates a unique key given two Id::Types
    *
    *   @description
    *     the key can be used to find an edge (within an unordered_map of edges) from its two end ids
    *     note that the order of id1 and id2 is not important
    *
    *   @param  id1 : element uniqueid enerated from Id class for one end
    *   @param  id2 : element2 uniqueid generated from Id class for other end
    */
  static EdgeKey makeKey(Id::Type id1, Id::Type id2);  ///<static function to create a unique key

private:
  /** Produces an EdgeType enumeration such as kEcalTrack
   the order of id1 an id2 does not matter,
   eg for one track and one ecal the type will always be kEcalTrack (and never be a kTrackEcal)
   */
  EdgeType makeEdgeType() const;

  IdType m_id1;         ///< long identifier for one end of the edge (order does not matter)
  IdType m_id2;         ///< long identifier for other end of ede (order does not matter)
  bool m_isLinked;      ///< boolean to day if there is a link between the two edges
  double m_distance;    ///< distance between two ends
  EdgeType m_edgeType;  ///<enum describing the edge type eg ecal-hcal or track-track
  EdgeKey m_key;        ///<unique key for this edge that allows lookup in an unordered_map of edges
};

}  // end namespace papas

#endif /* edge_h */
