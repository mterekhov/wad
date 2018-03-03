#include "aflat.h"
#include "apalete.h"
#import "atgaexporter.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AFlat::AFlat(unsigned char* incomingData, const std::string& incomingName, const APalete& palete) : _flatData(0), _flatName(incomingName)
{
	if (incomingData)
	{
		_flatData = convertData(incomingData, palete);
    }
}

//=============================================================================

AFlat::AFlat(const AFlat& flat) : _flatData(0), _flatName(flat._flatName)
{
	if (flat.flatDataSize())
	{
		_flatData = new unsigned char[flat.flatDataSize()];
		memcpy(_flatData, flat._flatData, flat.flatDataSize());
    }
}

//=============================================================================

AFlat::~AFlat()
{
	destroy();
}

//=============================================================================

void AFlat::destroy()
{
	if (_flatData)
	{
		delete [] _flatData;
		_flatName = "";
	}
}

//=============================================================================

AFlat& AFlat::operator=(const AFlat& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	destroy();

	_flatName = rv._flatName;
	_flatData = new unsigned char[rv.flatDataSize()];
	memcpy(_flatData, rv._flatData, rv.flatDataSize());
	
	return *this;
}

//=============================================================================

const std::string& AFlat::flatName() const
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

unsigned char* AFlat::convertData(unsigned char* incomingData, const APalete& palete)
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

    return outgoindData;
}

//=============================================================================

int AFlat::flatDataSize() const
{
	return 3 * flatWidthSize() * flatHeightSize();
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
