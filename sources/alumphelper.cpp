#include "alumphelper.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

const ALump& ALumpHelper::findLump(const std::string& lumpNameToFind, const TLumpsList& lumpsList)
{
	return *ALumpHelper::findLumpIter(lumpNameToFind, lumpsList);
}

//=============================================================================

TLumpsListConstIter ALumpHelper::findLumpIter(const std::string& lumpNameToFind, const TLumpsList& lumpsList)
{
	for (TLumpsListConstIter iter = lumpsList.begin(); iter < lumpsList.end(); iter++)
	{
		if ((*iter).lumpName == lumpNameToFind)
			return iter;
	}

	return lumpsList.end();
}

//=============================================================================

};  //  namespace spcWAD
