#ifndef SPCWAD_AFINDHELPER_H
#define SPCWAD_AFINDHELPER_H

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
class AFindHelper
{
public:
	static const AFlat& findFlat(const std::string& flatNameToFind, const TFlatsList& flatList);
	static const ALump& findLump(const std::string& lumpNameToFind, const TLumpsList& lumpsList);
	static TLumpsListConstIter findLumpIter(const std::string& lumpNameToFind, const TLumpsList& lumpsList);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AFINDHELPER_H
