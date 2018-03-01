#include "aflat.h"
#include "apalete.h"

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

std::string AFlat::flatName()
{
	return _flatName;
}

//=============================================================================

bool AFlat::saveFlatIntoTga(const std::string& fileName)
{
	if (!_flatData)
	{
		return false;
	}

	int width = flatWidthSize();
	int height = flatHeightSize();
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

    byte_1 = 24;
    fwrite(&byte_1, 1, 1, tgaFile); //  byte per pixel
    byte_1 = 0;
    fwrite(&byte_1, 1, 1, tgaFile); //  image property

    RGB2BGR(_flatData, width, height);
    flipOver(_flatData, width, height);
    if (fwrite(_flatData, 3 * width * height, 1, tgaFile) != 1) //  image data
    {
        return false;
	}
    flipOver(_flatData, width, height);
    RGB2BGR(_flatData, width, height);

    fclose(tgaFile);

	return true;
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

int AFlat::flatWidthSize()
{
	return 64;
}

//=============================================================================

int AFlat::flatHeightSize()
{
	return 64;
}

//=============================================================================

bool AFlat::RGB2BGR(unsigned char* data, int width, int height)
{
    if (!data)
        return true;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = 3 * (i * width + j);
            unsigned char tmp = data[index];
            data[index] = data[index + 2];
            data[index + 2] = tmp;
        }
    }

    return true;
}

//=============================================================================

bool AFlat::flipOver(unsigned char* data, int width, int height)
{
    if (!data)
        return true;

    unsigned char* tmp = new unsigned char[3 * width];
    for (int i = 0; i < height / 2; i++)
    {
        memcpy(tmp, &data[3 * i * width], 3 * width);
        memcpy(&data[3 * i * width], &data[3 * (height - i - 1) * width], 3 * width);
        memcpy(&data[3 * (height - i - 1) * width], tmp, 3 * width);
    }

	delete [] tmp;

    return true;
}

//=============================================================================

};  //  namespace spcWAD
