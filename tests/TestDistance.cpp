//
//  TestDistance.cpp
//  fastsim
//
//  Created by Alice Robson on 18/04/16.
//
//

#include "gtest/gtest.h"
#include "Distance.h"
#include "Id.h"
#include "Cluster.h"
#include "pTrack.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "Path.h"


namespace papas {

TEST(Distance, distance) {
  
  Cluster c1 {10, TVector3(1, 0, 0), 1., Id::ItemType::kEcalCluster};
  Cluster c2 {20, TVector3(1, 0, 0), 1., Id::ItemType::kHcalCluster};
  
  
  TVector3 p3 = c1.position().Unit()*100.;
  TLorentzVector p4{};
  p4.SetVectM(p3, 1.);
  std::shared_ptr<Path> path =std::make_shared<Path>(p4, TVector3(0,0,0),20.);
  double charge = 1.;
  Track tr{p3, charge, path};
  path->addPoint(papas::Position::kEcalIn, c1.position());
  path->addPoint(papas::Position::kHcalIn, c2.position());
  
  Distance distc1t(c1, tr);
  EXPECT_EQ(distc1t.distance(),0.);
  EXPECT_TRUE(distc1t.isLinked());
  
  Distance distc2t(c2, tr);
  EXPECT_EQ(distc2t.distance(),0.);
  EXPECT_TRUE(distc2t.isLinked());

  Distance distc2c1(c1, c2);
  EXPECT_TRUE(distc2t.isLinked());
  
  Distance disttt{};
  EXPECT_FALSE(disttt.isLinked());
  
}

} // end namespace papas

