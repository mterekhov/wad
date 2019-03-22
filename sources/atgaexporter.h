#ifndef SPCWAD_ATGAEXPORTER_H
#define SPCWAD_ATGAEXPORTER_H

//=============================================================================

#include <string>

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class saves the images into tga file
*/
class ATGAExporter
{
public:

    /**
     Saves image data in tga file

     @param fileName name of file in which to save the data
     @param data image data in raw rgb format pixel by pixel, every pixel is 3 byte, byte for every color component
     @param width width of image
     @param height height of image
     @return true in case of success, or false in case of error
     */
    bool exportData(const std::string& fileName, unsigned char *data, const int width, const int height);

private:
    /**
     Convert rgb component sequence into bgr for tga format

     @param data data to convert, result of convertion places in this array
     @param width width of image
     @param height height of  image
     @return true in case of success, or false in case of error
     */
	bool RGB2BGR(unsigned char* data, int width, int height);
    
    /**
     rotates the image so the bottom becomes the top and the top becomes the bottom

     @param data data to convert, result of convertion places in this array
     @param width width of image
     @param height height of  image
     @return true in case of success, or false in case of error
     */
	bool flipOver(unsigned char* data, int width, int height);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ATGAEXPORTER_H
