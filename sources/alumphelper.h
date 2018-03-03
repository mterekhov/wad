#ifndef SPCWAD_ALUMPHELPER_H
#define SPCWAD_ALUMPHELPER_H

//=============================================================================

#include <string>

#include "alump.h"
#include "types.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class saves the images into tga file
*/
class ALumpHelper
{
public:
	static const ALump& findLump(const std::string& lumpNameToFind, const TLumpsList& lumpsList);
	static TLumpsListConstIter findLumpIter(const std::string& lumpNameToFind, const TLumpsList& lumpsList);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALUMPHELPER_H
