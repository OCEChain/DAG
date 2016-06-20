//
//  distance.cpp
//  fastsim
//
//  Created by Alice Robson on 01/02/16.
//
//

#include "Distance.h"
//#include "Id.h"
#include "Cluster.h"
#include "pTrack.h"
#include "deltar.h"
#include "Path.h"


namespace papas {

Distance::Distance(const Cluster& cluster1, const Cluster& cluster2) :
    m_distance(-1),
    m_isLinked(false)
{
  //TODO check this is a bottom layer cluster
  m_distance = deltaR(cluster1.position().Theta(),
                      cluster1.position().Phi(),
                      cluster2.position().Theta(),
                      cluster2.position().Phi());
  m_isLinked = (m_distance < cluster1.angularSize() + cluster2.angularSize());
}


  void Distance::setDistanceToPoint(TVector3 point, const Cluster& cluster)
{
  //TODO check bottom later cluster
      m_distance = (cluster.position()-point).Mag();
      m_isLinked = m_distance < cluster.size();
  
  //std::cout<<"Error this should not be reacheded unless is is an unmerged cluster";
  
  }

Distance::Distance() :
    m_distance(-1),
    m_isLinked(false)
{
  
}

Distance::Distance(bool islinked, double dist) :
m_distance(dist),
m_isLinked(islinked)
{
  
}

Distance::Distance(const Cluster& cluster,const Track& track)
: m_distance(-1), m_isLinked(false)
{
  papas::Position cyl_layer = papas::Position::kEcalIn;
  if (Id::isHcal(cluster.id())) {
    cyl_layer = papas::Position::kHcalIn;
  }
  if (track.path()->hasNamedPoint(cyl_layer)) { //check exists {
    TVector3 pos = track.path()->namedPoint(cyl_layer);
    setDistanceToPoint(pos, cluster);
  }
  //TODO throw error
}

} // end namespace papas


/*
int test_Distamce2() {
c1 = Cluster(10, TVector3(1, 0, 0), 4., 'ecal_in')
c2 = Cluster(20, TVector3(1, 0, 0), 4., 'hcal_in')
link_type, link_ok, distance = ruler(c1, c2)
self.assertTrue(link_ok)
self.assertEqual(distance, 0.)
pos3 = TVector3(c1.position)
pos3.RotateZ(0.059)
c3 = Cluster(30, pos3, 5, 'hcal_in')
link_type, link_ok, distance = ruler(c1, c3)
self.assertEqual(distance, 0.059)
}*/





//Implemented via datatypes.cc