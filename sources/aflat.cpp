#include "aflat.h"
#include "apalete.h"
#import "atgaexporter.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AFlat::AFlat(unsigned char* incomingData, const int incomingSize, const std::string& incomingName, const APalete& palete) : _flatData(0), _flatSize(0), _flatName(incomingName)
{
	if (incomingSize)
	{
		_flatData = convertData(incomingData, incomingSize, &_flatSize, palete);
    }
}

//=============================================================================

AFlat::AFlat(const AFlat& flat) : _flatData(0), _flatSize(flat._flatSize), _flatName(flat._flatName)
{
	if (flat._flatSize)
	{
		_flatData = new unsigned char[flat._flatSize];
		memcpy(_flatData, flat._flatData, flat._flatSize);
    }
}

//=============================================================================

AFlat::~AFlat()
{
	if (_flatSize)
	{
		_flatSize = 0;
		delete [] _flatData;
	}
}

//=============================================================================

AFlat& AFlat::operator=(const AFlat& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	if (_flatData && _flatSize)
	{
		delete [] _flatData;
		_flatSize = 0;
	}
	
	_flatName = rv._flatName;
	_flatSize = rv._flatSize;
	_flatData = new unsigned char[rv._flatSize];
	
	memcpy(_flatData, rv._flatData, rv._flatSize);
	
	return *this;
}

//=============================================================================

std::string AFlat::flatName() const
{
	return _flatName;
}

//=============================================================================

const unsigned char* AFlat::flatData() const
{
	return _flatData;
}

//=============================================================================

bool AFlat::saveFlatIntoTga(const std::string& fileName)
{
	ATGAExporter tgaExporter;
	return tgaExporter.exportData(fileName, _flatData, flatWidthSize(), flatHeightSize());
}

//=============================================================================

#pragma mark - Private -

//=============================================================================

unsigned char* AFlat::convertData(unsigned char* incomingData, const int incomingSize, int* outgoindSize, const APalete& palete)
{
	const int flatWidth = flatWidthSize();
	const int flatHeight = flatHeightSize();
	
    //  convert paleted data into usual 24-bit image
    int size = flatWidth * flatHeight * 3;
    unsigned char* outgoindData = new unsigned char[size];
    memset(outgoindData, 0, size);
	
    for (int i = 0; i < flatHeight; i++)
    {
        for (int j = 0; j < flatWidth; j++)
        {
            int index = incomingData[flatWidth * i + j];
            outgoindData[3 * flatWidth * i + 3 * j] = palete.red(index);
            outgoindData[3 * flatWidth * i + 3 * j + 1] = palete.green(index);
            outgoindData[3 * flatWidth * i + 3 * j + 2] = palete.blue(index);
        }
    }

	*outgoindSize = size;
    return outgoindData;
}

//=============================================================================

int AFlat::flatWidthSize() const
{
	return 64;
}

//=============================================================================

int AFlat::flatHeightSize() const
{
	return 64;
}

//=============================================================================

};  //  namespace spcWAD
