//
//  Ruler.hpp
//  fastsim
//
//  Created by Alice Robson on 17/04/16.
//
//

#ifndef Ruler_h
#define Ruler_h

#include "Cluster.h"
#include "pTrack.h"


namespace papas {

class Distance;

// TODO template on Distance class?
class Ruler {

public:
  Ruler() {};
  Distance clusterClusterDistance(const Cluster& cluster1, const Cluster& cluster2) const;
  Distance clusterTrackDistance(const Cluster& cluster, const Track& track) const;


};
}  // end namespace papas

#endif /* Ruler_hpp */
