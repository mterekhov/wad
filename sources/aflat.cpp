#include "aflat.h"
#include "apalete.h"
#import "atgaexporter.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AFlat::AFlat(unsigned char* incomingData, const std::string& incomingName, const APalete& palete) : _imageData(64, 64), _flatName(incomingName)
{
    convertData(incomingData, palete);
}

//=============================================================================

AFlat::AFlat(const AFlat& flat) : _imageData(flat._imageData), _flatName(flat._flatName)
{
}

//=============================================================================

AFlat::~AFlat()
{
}

//=============================================================================

AFlat& AFlat::operator=(const AFlat& rv)
{
	if (this == &rv)
	{
		return *this;
	}

    _flatName = rv._flatName;
    _imageData = rv._imageData;
    
	return *this;
}

//=============================================================================

const std::string& AFlat::flatName() const
{
	return _flatName;
}

//=============================================================================

bool AFlat::saveFlatIntoTga(const std::string& fileName)
{
    return _imageData.exportIntoTga(fileName);
}

//=============================================================================

#pragma mark - Private -

//=============================================================================

void AFlat::convertData(unsigned char* incomingData, const APalete& palete)
{
	const int flatWidth = _imageData.width();
	const int flatHeight = _imageData.height();
	
    unsigned char* outgoindData = _imageData.data();
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
}

//=============================================================================

};  //  namespace spcWAD
