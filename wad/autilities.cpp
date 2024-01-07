#include "autilities.h"
#include "aflat.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

TLumpsList AUtilities::findLumpsList(const std::string& lumpsNameMask, const TLumpsList& lumpsList)
{
	TLumpsList founded;
	for (TLumpsListConstIter iter = lumpsList.begin(); iter != lumpsList.end(); iter++)
	{
		if (AUtilities::stringPrefixCompare(lumpsNameMask, iter->lumpName))
		{
			founded.push_back(*iter);
		}
	}

	return founded;
}

//=============================================================================

TLumpsListConstIter AUtilities::findLumpIter(const std::string& lumpNameToFind, const TLumpsList& lumpsList)
{
	for (TLumpsListConstIter iter = lumpsList.begin(); iter != lumpsList.end(); iter++)
	{
		if (AUtilities::stringCompare(iter->lumpName, lumpNameToFind))
		{
			return iter;
		}
	}

	return lumpsList.end();
}

//=============================================================================

const AFlat& AUtilities::findFlat(const std::string& flatNameToFind, const TFlatsList& flatList)
{
	for (TFlatsListConstIter iter = flatList.begin(); iter != flatList.end(); iter++)
	{
	    if (!strncmp(iter->flatName().c_str(), flatNameToFind.c_str(), iter->flatName().length()))
		{
			return (*iter);
		}
	}

	return *flatList.end();
}

//=============================================================================

bool AUtilities::readLumpData(FILE* wadFile, const ALump& lumpToRead, unsigned char *lumpData)
{
	if (fseek(wadFile, lumpToRead.lumpOffset, SEEK_SET))
	{
		return false;
	}
	
	memset(lumpData, 0, lumpToRead.lumpSize);
	int read = fread(lumpData, lumpToRead.lumpSize, 1, wadFile);
	if (read != 1)
	{
		return false;
	}
	
	return true;
}

//=============================================================================

bool AUtilities::stringCompare(const std::string& one, const std::string& two)
{
	std::string oneCase;
	oneCase.resize(one.size());
	std::transform(one.begin(),
				   one.end(),
				   oneCase.begin(),
				   ::tolower);

	std::string twoCase;
	twoCase.resize(two.size());
	std::transform(two.begin(),
				   two.end(),
				   twoCase.begin(),
				   ::tolower);
	if (!oneCase.compare(twoCase))
	{
		return true;
	}
	
	return false;
}

//=============================================================================

bool AUtilities::stringPrefixCompare(const std::string& prefix, const std::string& string)
{
	std::string prefixCase;
	prefixCase.resize(prefix.size());
	std::transform(prefix.begin(),
				   prefix.end(),
				   prefixCase.begin(),
				   ::tolower);

	std::string stringCase;
	stringCase.resize(string.size());
	std::transform(string.begin(),
				   string.end(),
				   stringCase.begin(),
				   ::tolower);
	
	if (stringCase.rfind(prefixCase, 0) == 0)
	{
		return true;
	}

	return false;
}

//=============================================================================

};  //  namespace spcWAD
