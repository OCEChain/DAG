//
//  Ruler.hpp
//  fastsim
//
//  Created by Alice Robson on 17/04/16.
//
//

#ifndef Ruler_h
#define Ruler_h

#include <stdio.h>
#include "Id.h"

namespace papas {
  
class Cluster;
class Track;
class Distance;
class PFEvent;



//TODO template on Distance class
class Ruler {
  
public:
  Ruler (const PFEvent& pfevent);
  Distance distance(Id::Type id1, Id::Type id2) const;
private:
  Distance clusterClusterDistance(Id::Type id1, Id::Type id2) const;
  Distance clusterClusterDistance(const Cluster& cluster1, const Cluster& cluster2) const;
  Distance clusterTrackDistance(Id::Type id1, Id::Type id2) const;
  Distance clusterTrackDistance(const Cluster& cluster, const Track& track)  const;
  
  Distance distance() const;
  
  const PFEvent& m_pfEvent;
};
} // end namespace papas

#endif /* Ruler_hpp */
