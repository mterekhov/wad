#ifndef SPCWAD_AIMAGEDATA_H
#define SPCWAD_AIMAGEDATA_H

//=============================================================================

#include <string>

#include "alump.h"
#include "apalete.h"

//=============================================================================

class ALump;

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
 This class is a storage for any picture. Such storage is a raw pixel in rgb-format
 */
class AImageData
{
public:
    AImageData();
    AImageData(const int imageWidth, const int imageHeight);
    ~AImageData();
    AImageData(const AImageData& image);
    AImageData& operator=(const AImageData& rv);
    
    unsigned char* data();
    int height() const;
    int width() const;
    int dataSize() const;
    bool exportIntoTga(const std::string& fileName);
    
private:
    void destroy();
    
    unsigned char* _data;
    short _width;
    short _height;
};

//=============================================================================
    
};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AIMAGEDATA_H
