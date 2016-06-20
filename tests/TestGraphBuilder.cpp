#include "gtest/gtest.h"
#include "GraphBuilder.h"
#include "Id.h"
#include "Edge.h"
#include "Definitions.h"

namespace papas {

TEST(GraphBuilder, one) {
  
  Id::Type id1 = Id::makeEcalId();
  Id::Type id2 = Id::makeHcalId();
  Id::Type id3 = Id::makeTrackId();
  
  Id::Type id4 = Id::makeEcalId();
  Id::Type id5 = Id::makeHcalId();
  Id::Type id6 = Id::makeTrackId();
  
  std::vector<Id::Type> ids {id1,id2,id3, id4,id5,id6};
  
  Edge edge =  Edge(id1, id2, false, 0.00023);
  Edge edge1 = Edge(id1, id3, true, 10030.0);
  Edge edge2 = Edge(id2, id3, true, 0.00005);
  
  Edge edge4 = Edge(id4, id5, false, 3.1234);
  Edge edge5 = Edge(id4, id6, true, 0.1234);
  Edge edge6 = Edge(id5, id6, true, 123.0);
  
  Edges edges;
  
  edges.emplace(edge.key(),  std::move(edge));
  edges.emplace(edge1.key(), std::move(edge1));
  edges.emplace(edge2.key(), std::move(edge2));
  edges.emplace(edge4.key(), std::move(edge4));
  edges.emplace(edge5.key(), std::move(edge5));
  edges.emplace(edge6.key(), std::move(edge6));
  
  ASSERT_EQ(edges.size() , 6UL);
  
  
  
  auto graphbuilder = GraphBuilder(ids, edges);
  
  ASSERT_EQ(graphbuilder.subGraphs().size() , 2UL);
  ASSERT_EQ(graphbuilder.subGraphs()[0].size(),3UL);
  
  //std::cout<<graphbuilder;

}
  
} // end namespace papas
