#include "apatch.h"
#include "apalete.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

APatch::APatch(unsigned char* incomingData, const int incomingWidth, const int incomingHeight, const std::string& incomingName, const APalete& palete) : _patchData(0), _patchWidth(incomingWidth), _patchHeight(incomingHeight), _patchName(incomingName)
{
}

//=============================================================================

APatch::APatch(const APatch& patch) : _patchData(0), _patchWidth(patch._patchWidth), _patchHeight(patch._patchHeight), _patchName(patch._patchName)
{
	if (patch.patchDataSize())
	{
		_patchData = new unsigned char[patch.patchDataSize()];
		memcpy(_patchData, patch._patchData, patch.patchDataSize());
    }
}

//=============================================================================

APatch::~APatch()
{
	if (patchDataSize())
	{
		_patchHeight = 0;
		_patchWidth = 0;
		delete [] _patchData;
	}
}

//=============================================================================

APatch& APatch::operator=(const APatch& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	if (patchDataSize())
	{
		delete [] _patchData;
		_patchHeight = 0;
		_patchWidth = 0;
	}
	
	_patchName = rv._patchName;
	_patchHeight = rv._patchHeight;
	_patchWidth = rv._patchWidth;
	
	_patchData = new unsigned char[rv.patchDataSize()];
	memcpy(_patchData, rv._patchData, rv.patchDataSize());
	
	return *this;
}

//=============================================================================

int APatch::patchDataSize() const
{
	return 3 * _patchHeight * _patchWidth;
}

//=============================================================================

};  //  namespace spcWAD
