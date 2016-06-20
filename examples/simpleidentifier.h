//
//  simpleidentifier.h
//
//  Created by Alice Robson on 05/01/16.
//
//

#ifndef simpleidentifier_h
#define simpleidentifier_h



enum class enumDataType {PARTICLE, TRACK, CLUSTER};
enum class enumSubType {RAW, MERGED, SMEARED};

class Id {
public:
   Id() {};
   static long makeId(enumDataType datatype, enumSubType subtype);
   //Access stored Identifier information
   static enumDataType        dataType(long id);
   static enumSubType         subType(long id);
   static int uniqueId(long id);
private:
   static int s_counter;
};




#endif /* simpleidentifier_h */
