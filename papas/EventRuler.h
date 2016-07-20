//
//  EventRuler.h
//  fastsim
//
//  Created by Alice Robson on 17/04/16.
//
//

#ifndef EventRuler_h
#define EventRuler_h

#include "Cluster.h"
#include "Id.h"
#include "Ruler.h"
#include "pTrack.h"
#include <stdio.h>

namespace papas {

class Distance;
class PFEvent;

class EventRuler {

public:
  EventRuler(const PFEvent& pfevent);
  Distance distance(Id::Type id1, Id::Type id2) const;

private:
  Distance clusterClusterDistance(Id::Type id1, Id::Type id2) const;
  Distance clusterTrackDistance(Id::Type id1, Id::Type id2) const;

  Ruler m_ruler;
  const PFEvent& m_pfEvent;
};
}  // end namespace papas

#endif /* EventRuler_hpp */