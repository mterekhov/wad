#include "afindhelper.h"
#include "aflat.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

const ALump& AFindHelper::findLump(const std::string& lumpNameToFind, const TLumpsList& lumpsList)
{
	return *AFindHelper::findLumpIter(lumpNameToFind, lumpsList);
}

//=============================================================================

TLumpsListConstIter AFindHelper::findLumpIter(const std::string& lumpNameToFind, const TLumpsList& lumpsList)
{
	for (TLumpsListConstIter iter = lumpsList.begin(); iter < lumpsList.end(); iter++)
	{
		if ((*iter).lumpName == lumpNameToFind)
			return iter;
	}

	return lumpsList.end();
}

//=============================================================================

const AFlat& AFindHelper::findFlat(const std::string& flatNameToFind, const TFlatsList& flatList)
{
	for (TFlatsListConstIter iter = flatList.begin(); iter < flatList.end(); iter++)
	{
		if (iter->flatName() == flatNameToFind)
		{
			return (*iter);
		}
	}

	return *flatList.end();
}

//=============================================================================

};  //  namespace spcWAD
