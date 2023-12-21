#include "atgaexporter.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

bool ATGAExporter::exportData(const std::string& fileName, unsigned char *data, const int width, const int height, const int bytesPerPixel)
{
    if (!data)
    {
        return false;
    }

    unsigned char byte_1 = 0;
    unsigned short byte_2 = 0;
    FILE* tgaFile = fopen(fileName.c_str(), "wb");
    if (!tgaFile)
        return false;

    fwrite(&byte_1, 1, 1, tgaFile); //  identity length
    fwrite(&byte_1, 1, 1, tgaFile); //  palete type
    byte_1 = 2;
    fwrite(&byte_1, 1, 1, tgaFile); //  image type
    byte_1 = 0;
    fwrite(&byte_2, 2, 1, tgaFile); //  palete offset
    fwrite(&byte_2, 2, 1, tgaFile); //  palete size
    fwrite(&byte_1, 1, 1, tgaFile); //  palete bpp
    fwrite(&byte_2, 2, 1, tgaFile); //  x coord
    fwrite(&byte_2, 2, 1, tgaFile); //  y coord

    byte_2 = width;
    fwrite(&byte_2, 2, 1, tgaFile); //  image width
    byte_2 = height;
    fwrite(&byte_2, 2, 1, tgaFile); //  image height

    byte_1 = 8 * bytesPerPixel;
    fwrite(&byte_1, 1, 1, tgaFile); //  byte per pixel
    byte_1 = 0;
    fwrite(&byte_1, 1, 1, tgaFile); //  image property

    RGB2BGR(data, width, height, bytesPerPixel);
    flipOver(data, width, height, bytesPerPixel);
    if (fwrite(data, bytesPerPixel * width * height, 1, tgaFile) != 1) //  image data
    {
        return false;
    }
    flipOver(data, width, height, bytesPerPixel);
    RGB2BGR(data, width, height, bytesPerPixel);

    fclose(tgaFile);

    return true;
}

//=============================================================================

bool ATGAExporter::RGB2BGR(unsigned char* data, int width, int height, const int bytesPerPixel)
{
    if (!data)
        return true;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index =  bytesPerPixel * (i * width + j);
            unsigned char tmp = data[index];
            data[index] = data[index + 2];
            data[index + 2] = tmp;
        }
    }

    return true;
}

//=============================================================================

bool ATGAExporter::flipOver(unsigned char* data, int width, int height, const int bytesPerPixel)
{
    if (!data)
        return true;

    unsigned char* tmp = new unsigned char[bytesPerPixel * width];
    for (int i = 0; i < height / 2; i++)
    {
        memcpy(tmp, &data[bytesPerPixel * i * width], bytesPerPixel * width);
        memcpy(&data[bytesPerPixel * i * width], &data[bytesPerPixel * (height - i - 1) * width], bytesPerPixel * width);
        memcpy(&data[bytesPerPixel * (height - i - 1) * width], tmp, bytesPerPixel * width);
    }

    delete [] tmp;

    return true;
}

//=============================================================================

};  //  namespace spcWAD
