#ifndef SPCWAD_TYPES_H
#define SPCWAD_TYPES_H

//=============================================================================

#include <vector>

//=============================================================================

namespace spcWAD
{

//=============================================================================

class ALump;

//=============================================================================

typedef std::vector<ALump*> TSequence;
typedef std::vector<ALump*>::iterator TSeqIter;

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_TYPES_H

