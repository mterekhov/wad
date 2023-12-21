#include "aimagedata.h"
#include "atgaexporter.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AImageData::AImageData() : _data(0), _width(0), _height(0), _bytesPerPixel(0)
{
    
}

//=============================================================================

AImageData::AImageData(const int imageWidth, const int imageHeight, const int bytesPerPixel) : _data(0), _width(imageWidth), _height(imageHeight), _bytesPerPixel(bytesPerPixel)
{
    if (dataSize() == 0)
    {
        return;
    }
    
    _data = new unsigned char[dataSize()];
    memset(_data, TransparentPixel, dataSize());
}

//=============================================================================

AImageData::AImageData(const AImageData& imageCopy) : _data(0), _width(imageCopy._width), _height(imageCopy._height), _bytesPerPixel(imageCopy._bytesPerPixel)
{
    if (dataSize() == 0)
    {
        return;
    }

    _data = new unsigned char[dataSize()];
    memcpy(_data, imageCopy._data, dataSize());
}

//=============================================================================

AImageData::~AImageData()
{
    destroy();
}

//=============================================================================

AImageData& AImageData::operator=(const AImageData& rv)
{
    if (this == &rv)
    {
        return *this;
    }
    
    destroy();
    
    _height = rv._height;
    _width = rv._width;
    _bytesPerPixel = rv._bytesPerPixel;
    
    _data = new unsigned char[dataSize()];
    memcpy(_data, rv._data, dataSize());
    
    return *this;
}

//=============================================================================

void AImageData::destroy()
{
    if (_data)
    {
        delete [] _data;
        _data = 0;
        _height = 0;
        _width = 0;
        _bytesPerPixel = 0;
    }
}

//=============================================================================

bool AImageData::exportIntoTga(const std::string& fileName)
{
    ATGAExporter tgaExporter;
    return tgaExporter.exportData(fileName, _data, _width, _height, _bytesPerPixel);
}

//=============================================================================

unsigned char* AImageData::data() const
{
    return _data;
}

//=============================================================================

int AImageData::dataSize() const
{
    return _bytesPerPixel * _width * _height;
}

//=============================================================================

int AImageData::height() const
{
    return _height;
}

//=============================================================================

int AImageData::bytesPerPixel() const
{
    return _bytesPerPixel;
}

//=============================================================================

int AImageData::width() const
{
    return _width;
}

//=============================================================================

AImageData AImageData::mirrorImage() const
{
    AImageData mirroredData(width(), height(), bytesPerPixel());
    unsigned char *dstData = mirroredData._data;
    unsigned char *srcData = _data;
    for (int columnIndex = 0; columnIndex < width(); columnIndex++)
    {
        for (int i = 0; i < height(); i++)
        {
            int colorIndex = columnIndex + i * width();
            int dstIndex = width() * (i + 1) - columnIndex - 1;
            for (int bpp = 0; bpp < bytesPerPixel(); bpp++)
            {
                dstData[bytesPerPixel() * dstIndex + bpp] = srcData[bytesPerPixel() * colorIndex + bpp];
            }
        }
    }
    
    return mirroredData;
}

//=============================================================================
    
};  //  namespace spcWAD
