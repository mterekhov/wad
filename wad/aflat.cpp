#include "aflat.h"
#include "apalete.h"
#import "atgaexporter.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AFlat::AFlat(unsigned char* incomingData, const std::string& incomingName, const APalete& palete) : _imageData(64, 64, 4), _flatName(incomingName)
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

const AImageData& AFlat::imageData() const
{
    return _imageData;
}

//=============================================================================

#pragma mark - Private -

//=============================================================================

void AFlat::convertData(unsigned char* incomingData, const APalete& palete)
{
    const int flatWidth = _imageData.width();
    const int flatHeight = _imageData.height();
    
    unsigned char* outgoindData = _imageData.data();
    int bytesPerPixel = _imageData.bytesPerPixel();
    for (int i = 0; i < flatHeight; i++)
    {
        for (int j = 0; j < flatWidth; j++)
        {
            int index = incomingData[flatWidth * i + j];
            outgoindData[bytesPerPixel * flatWidth * i + bytesPerPixel * j] = palete.red(index);
            outgoindData[bytesPerPixel * flatWidth * i + bytesPerPixel * j + 1] = palete.green(index);
            outgoindData[bytesPerPixel * flatWidth * i + bytesPerPixel * j + 2] = palete.blue(index);
            outgoindData[bytesPerPixel * flatWidth * i + bytesPerPixel * j + 3] = TransparentPixel;
        }
    }
}

//=============================================================================

};  //  namespace spcWAD
