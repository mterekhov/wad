#ifndef SPCWAD_TYPES_H
#define SPCWAD_TYPES_H

//=============================================================================

#include <vector>

//=============================================================================

namespace spcWAD
{

//=============================================================================

class ALump;
class ADemo;
class AFlat;
class APatch;

//=============================================================================

typedef std::vector<ALump> TLumpsList;
typedef TLumpsList::iterator TLumpsListIter;
typedef std::vector<ADemo> TDemosList;
typedef TDemosList::iterator TDemosListIter;
typedef std::vector<AFlat> TFlatsList;
typedef TFlatsList::iterator TFlatsListIter;
typedef std::vector<APatch> TPatchesList;
typedef TPatchesList::iterator TPatchesListIter;

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_TYPES_H

