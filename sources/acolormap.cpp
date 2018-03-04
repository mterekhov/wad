#include "acolormap.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AColorMap::AColorMap(unsigned char* incomingData, const int incomingSize) : _mapcolorData(0), _mapcolorSize(incomingSize)
{
	if (incomingSize)
	{
		_mapcolorData = new unsigned char[incomingSize];
		memcpy(_mapcolorData, incomingData, incomingSize);
    }
}

//=============================================================================

AColorMap::~AColorMap()
{
	destroy();
}

//=============================================================================

void AColorMap::destroy()
{
	if (_mapcolorSize)
	{
		_mapcolorSize = 0;
		delete [] _mapcolorData;
		_mapcolorData = 0;
	}
}

//=============================================================================

AColorMap& AColorMap::operator=(const AColorMap& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	if (_mapcolorData && _mapcolorSize)
	{
		delete [] _mapcolorData;
		_mapcolorSize = 0;
	}
	
	_mapcolorSize = rv._mapcolorSize;
	_mapcolorData = new unsigned char[rv._mapcolorSize];
	memcpy(_mapcolorData, rv._mapcolorData, rv._mapcolorSize);
	
	return *this;
}

//=============================================================================

};  //  namespace spcWAD
