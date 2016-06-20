#include "edge.h"


namespace papas {

Edge::Edge(Id::Type id1, Id::Type id2, bool isLinked, double distance) :
m_id1(id1),
m_id2(id2),
m_isLinked(isLinked),
m_distance(distance),
m_edgeType(makeEdgeType()),
m_key(Edge::makeKey(id1, id2))
{
}


/** Static function. Makes a unique key that can be used to locate the required edge
 */
Edge::EdgeKey Edge::makeKey(Id::Type id1, Id::Type id2) {

  EdgeKey key;
  Id::Type uid1 =Id::uniqueId(id1);
  Id::Type uid2 =Id::uniqueId(id2);
 
  if (id1 > id2) //ensure that the order of the ids does not matter
    key= (((uint64_t)uid1) << Id::bitshift) | ((uint64_t)uid2);
  else
    key= (((uint64_t)uid2) << Id::bitshift) | ((uint64_t)uid1);
  

  return key;
}

Id::Type Edge::otherid(Id::Type id) const
{
  if (m_id1==id)
    return m_id2;
  else if (m_id2==id)
    return m_id1;
  return 0;
}

Edge::EdgeType Edge::makeEdgeType() const {
  // Produces an EdgeType enumeration such as kEcalTrack
  // the order of id1 an id2 does not matter,
  // eg for one track and one ecal the type will always be kEcalTrack (and never be a kTrackEcal)
 
  //get one letter abbreviation of type eg 't' for a track
  auto shortid1 = Id::typeShortCode(m_id1);
  auto shortid2 = Id::typeShortCode(m_id2);
  
  /*if (Id::pretty(m_id1).compare(0,4, "h829")==0)
    std::cout <<"id1";
  */
  if (shortid1==shortid2) {
    if (shortid1== 'h')
      return EdgeType::kHcalHcal;
    else if (shortid1=='e')
      return EdgeType::kEcalEcal;
    else if (shortid1=='t')
      return EdgeType::kTrackTrack;
  }
  else if ((shortid1=='h' && shortid2=='t') || (shortid1=='t' && shortid2=='h'))
    return EdgeType::kHcalTrack;
  else if ((shortid1=='e' && shortid2=='t') || (shortid1=='t' && shortid2=='e'))
    return EdgeType::kEcalTrack;
  else if ((shortid1=='e' && shortid2=='h') || (shortid1=='h' && shortid2=='e'))
    return EdgeType::kEcalHcal;
  return EdgeType::kUnknown;
  
}


std::ostream& operator<<(std::ostream& os, const Edge& edge) {
  os << "Edge: " << edge.m_id1<<"<->"<<edge.m_id2<<": " << edge.m_distance;
  os << " (link = " << std::boolalpha << edge.m_isLinked << ")" ;
  return os;
}



} // end namespace papas

int test_edges() {
  using namespace papas;
  Id::Type id1=Id::makeEcalId();
  Id::Type id2=Id::makeHcalId();
  Id::Type id3=Id::makeTrackId();
  
  Edge edge=Edge(id1,id2,false,0.0);
  Edge edge1=Edge(id1,id3,true,0.0);
  //Edge edge2=Edge(id2,id3,true,0.0);
  
  std::cout<<edge1<<std::endl;
  std::cout<<edge<<std::endl;
  
  return 0;
}
