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

ADemo::ADemo(const ADemo& demo) : _demoData(0), _demoSize(demo._demoSize), _demoName(demo._demoName)
{
	if (demo._demoSize)
	{
		_demoData = new unsigned char[demo._demoSize];
		memcpy(_demoData, demo._demoData, demo._demoSize);
    }
}

//=============================================================================

ADemo::~ADemo()
{
	destroy();
}

//=============================================================================

void ADemo::destroy()
{
	if (_demoSize)
	{
		_demoSize = 0;
		delete [] _demoData;
		_demoData = 0;
	}
}

//=============================================================================

ADemo& ADemo::operator=(const ADemo& rv)
{
	if (this == &rv)
	{
		return *this;
	}

	destroy();
	
	_demoName = rv._demoName;
	_demoSize = rv._demoSize;
	_demoData = new unsigned char[rv._demoSize];
	
	memcpy(_demoData, rv._demoData, rv._demoSize);
	
	return *this;
}

//=============================================================================

};  //  namespace spcWAD
