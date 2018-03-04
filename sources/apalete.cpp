#include "apalete.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

APalete::APalete(unsigned char* incomingData, const int incomingSize) : _paleteData(0), _paleteSize(incomingSize)
{
	if (incomingSize)
	{
		_paleteData = new unsigned char[incomingSize];
		memcpy(_paleteData, incomingData, incomingSize);
    }
}

//=============================================================================

APalete::~APalete()
{
	destroy();
}

//=============================================================================

void APalete::destroy()
{
	if (_paleteSize)
	{
		_paleteSize = 0;
		delete [] _paleteData;
		_paleteData = 0;
	}
}

//=============================================================================

APalete& APalete::operator=(const APalete& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	destroy();

	_paleteSize = rv._paleteSize;
	_paleteData = new unsigned char[rv._paleteSize];
	memcpy(_paleteData, rv._paleteData, rv._paleteSize);
	
	return *this;
}

//=============================================================================

const unsigned char APalete::red(const int index) const
{
    if (!_paleteData)
    {
        return 0;
	}

    return _paleteData[3 * index];
}

//=============================================================================

const unsigned char APalete::green(const int index) const
{
    if (!_paleteData)
    {
        return 0;
	}

    return _paleteData[3 * index + 1];
}

//=============================================================================

const unsigned char APalete::blue(const int index) const
{
    if (!_paleteData)
    {
        return 0;
	}

    return _paleteData[3 * index + 2];
}

//=============================================================================

};  //  namespace spcWAD
