#include "ademo.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ADemo::ADemo(unsigned char* incomingData, const int incomingSize, const std::string& incomingName) : _demoData(0), _demoSize(incomingSize), _demoName(incomingName)
{
	if (incomingSize)
	{
		_demoData = new unsigned char[incomingSize];
		memcpy(_demoData, incomingData, incomingSize);
    }
}

//=============================================================================

ADemo::~ADemo()
{
	if (_demoSize)
	{
		_demoSize = 0;
		delete [] _demoData;
	}
}

//=============================================================================

ADemo& ADemo::operator=(const ADemo& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	if (_demoData && _demoSize)
	{
		delete [] _demoData;
		_demoSize = 0;
	}
	
	_demoName = rv._demoName;
	_demoSize = rv._demoSize;
	_demoData = new unsigned char[rv._demoSize];
	
	memcpy(_demoData, rv._demoData, rv._demoSize);
	
	return *this;
}

//=============================================================================

};  //  namespace spcWAD
