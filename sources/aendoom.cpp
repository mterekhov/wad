#include "aendoom.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AEnDoom::AEnDoom(unsigned char* incomingData, const int incomingSize) : _endoomData(0), _endoomSize(incomingSize)
{
	if (incomingSize)
	{
		_endoomData = new unsigned char[incomingSize];
		memcpy(_endoomData, incomingData, incomingSize);
    }
}

//=============================================================================

AEnDoom::~AEnDoom()
{
	if (_endoomSize)
	{
		_endoomSize = 0;
		delete [] _endoomData;
	}
}

//=============================================================================

AEnDoom& AEnDoom::operator=(const AEnDoom& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	if (_endoomData && _endoomSize)
	{
		delete [] _endoomData;
		_endoomSize = 0;
	}
	
	_endoomSize = rv._endoomSize;
	_endoomData = new unsigned char[rv._endoomSize];
	memcpy(_endoomData, rv._endoomData, rv._endoomSize);
	
	return *this;
}

//=============================================================================

};  //  namespace spcWAD
