#ifndef SPCWAD_AUTILITIES_H
#define SPCWAD_AUTILITIES_H

//=============================================================================

#include <string>

#include "alump.h"
#include "types.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	Some utilities
*/
class AUtilities
{
public:
	static TLumpsList findLumpsList(const std::string& lumpsNameMask, const TLumpsList& lumpsList);
	static const AFlat& findFlat(const std::string& flatNameToFind, const TFlatsList& flatList);
	static TLumpsListConstIter findLumpIter(const std::string& lumpNameToFind, const TLumpsList& lumpsList);
	static bool readLumpData(FILE* wadFile, const ALump& lumpToRead, unsigned char *lumpData);
	static bool stringCompare(const std::string& one, const std::string& two);
	static bool stringPrefixCompare(const std::string& prefix, const std::string& string);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AUTILITIES_H
