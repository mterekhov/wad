#include "aimagedata.h"
#include "atgaexporter.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AImageData::AImageData() : _data(0), _width(0), _height(0)
{
    
}

//=============================================================================

AImageData::AImageData(const int imageWidth, const int imageHeight) : _data(0), _width(imageWidth), _height(imageHeight)
{
    if (dataSize() == 0)
    {
        return;
    }
    
    _data = new unsigned char[dataSize()];
    memset(_data, 0, dataSize());
}

//=============================================================================

AImageData::AImageData(const AImageData& imageCopy) : _data(0), _width(imageCopy._width), _height(imageCopy._height)
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
    
    _data = new unsigned char[rv.dataSize()];
    memcpy(_data, rv._data, rv.dataSize());
    
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
    }
}

//=============================================================================

bool AImageData::exportIntoTga(const std::string& fileName)
{
    ATGAExporter tgaExporter;
    return tgaExporter.exportData(fileName, _data, _width, _height);
}

//=============================================================================

unsigned char* AImageData::data()
{
    return _data;
}

//=============================================================================

int AImageData::dataSize() const
{
    return 3 * _width * _height;
}

//=============================================================================

int AImageData::height() const
{
    return _height;
}

//=============================================================================

int AImageData::width() const
{
    return _width;
}

//=============================================================================
    
};  //  namespace spcWAD
