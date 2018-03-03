#include "afindhelper.h"
#include "aflat.h"
#include "apatch.h"

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
	    if (!strncmp(iter->lumpName.c_str(), lumpNameToFind.c_str(), iter->lumpName.length()))
		{
			return iter;
		}
	}

	return lumpsList.end();
}

//=============================================================================

const AFlat& AFindHelper::findFlat(const std::string& flatNameToFind, const TFlatsList& flatList)
{
	for (TFlatsListConstIter iter = flatList.begin(); iter < flatList.end(); iter++)
	{
		printf("<%s>\n", iter->flatName().c_str());
	    if (!strncmp(iter->flatName().c_str(), flatNameToFind.c_str(), iter->flatName().length()))
		{
			return (*iter);
		}
	}

	return *flatList.end();
}

//=============================================================================

APatch& AFindHelper::findPatch(const int patchIndex, TPatchesList& patchesList)
{
//	for (TPatchesListIter iter = patchesList.begin(); iter < patchesList.end(); iter++)
//	{
//	    if (iter->patchIndex == patchIndex)
//		{
//			return (*iter);
//		}
//	}

	return *patchesList.end();
}

//=============================================================================

const APatch& AFindHelper::findPatch(const int patchIndex, const TPatchesList& patchesList)
{
//	for (TPatchesListConstIter iter = patchesList.begin(); iter < patchesList.end(); iter++)
//	{
//	    if (iter->patchIndex == patchIndex)
//		{
//			return (*iter);
//		}
//	}

	return *patchesList.end();
}

//=============================================================================

};  //  namespace spcWAD
