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

//=============================================================================

typedef std::vector<ALump> TLumpsList;
typedef TLumpsList::iterator TLumpsListIter;
typedef std::vector<ADemo> TDemosList;
typedef TDemosList::iterator TDemosListIter;
typedef std::vector<AFlat> TFlatsList;
typedef TFlatsList::iterator TFlatsListIter;

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_TYPES_H

