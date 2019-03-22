#include "apicture.h"
#include "apalete.h"
#include "atgaexporter.h"
#include "types.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

APicture::APicture() : _patchName("")
{
    
}

//=============================================================================

APicture::APicture(const unsigned char* incomingData, const std::string& incomingName, const APalete& palete) : _patchName(incomingName)
{
	if (incomingData)
	{
		int bytesOffset = 0;
        short width = 0;
		memcpy(&width, &incomingData[bytesOffset], 2);
		bytesOffset += 2;
        short height = 0;
		memcpy(&height, &incomingData[bytesOffset], 2);
		bytesOffset += 2;

		bytesOffset += 4;	//	skiping offsets
        imageData = AImageData(width, height);
		convertData(incomingData, palete, bytesOffset);
    }
}

//=============================================================================

APicture::APicture(const APicture& patch) : imageData(patch.imageData), _patchName(patch._patchName)
{
}

//=============================================================================

APicture::~APicture()
{
}

//=============================================================================

APicture& APicture::operator=(const APicture& rv)
{
	if (this == &rv)
	{
		return *this;
	}

    _patchName = rv._patchName;
    imageData = rv.imageData;
    
	return *this;
}

//=============================================================================

const std::string& APicture::patchName() const
{
	return _patchName;
}

//=============================================================================

bool APicture::savePatchIntoTga(const std::string& fileName)
{
    return imageData.exportIntoTga(fileName);
}

//=============================================================================

void APicture::convertData(const unsigned char* incomingData, const APalete& palete, const int bytesOffset)
{
	int bytesOffsetPointer = bytesOffset;

    int* columnOffsets = new int[imageData.width()];
    memset(columnOffsets, 0, 4 * imageData.width());
    for (int i = 0; i < imageData.width(); i++)
    {
		memcpy(&columnOffsets[i], &incomingData[bytesOffsetPointer], 4);
		bytesOffsetPointer += 4;
	}

	unsigned char* convertedData = imageData.data();
    memset(convertedData, PIXEL_TRANSPARENCY_MARKER, imageData.dataSize());
    for (int i = 0; i < imageData.width(); i++)
    {
    	int currentColumnDataOffset = columnOffsets[i];
	    unsigned char terminator = 0;
        while(true)
        {
            int rowNumber = 0;
			memcpy(&rowNumber, &incomingData[currentColumnDataOffset], 1);
			currentColumnDataOffset += 1;

			if (rowNumber == 0xFF)
			{
				break;
			}

            int rowSize = 0;
			memcpy(&rowSize, &incomingData[currentColumnDataOffset], 1);
			currentColumnDataOffset += 1;
			
			//	skip reserved byte
			currentColumnDataOffset += 1;

            unsigned char* data = new unsigned char[rowSize];
			memcpy(data, &incomingData[currentColumnDataOffset], rowSize);
			currentColumnDataOffset += rowSize;

            for (int j = 0; j < rowSize; j++)
            {
                int index = 3 * ((imageData.height() - (rowNumber + j + 1)) * imageData.width() + i);
                convertedData[index] = palete.red(data[j]);
                convertedData[index + 1] = palete.green(data[j]);
                convertedData[index + 2] = palete.blue(data[j]);
            }
            delete [] data;

			//	skip reserved byte
			currentColumnDataOffset += 1;

			memcpy(&terminator, &incomingData[currentColumnDataOffset], 1);
        }
    }
	delete [] columnOffsets;
	
    unsigned char* tmp = new unsigned char[3 * imageData.width()];
    for (int i = 0; i < imageData.height() / 2; i++)
    {
        memcpy(tmp, &convertedData[3 * i * imageData.width()], 3 * imageData.width());
        memcpy(&convertedData[3 * i * imageData.width()], &convertedData[3 * (imageData.height() - i - 1) * imageData.width()], 3 * imageData.width());
        memcpy(&convertedData[3 * (imageData.height() - i - 1) * imageData.width()], tmp, 3 * imageData.width());
    }
    
    delete [] tmp;
}

//=============================================================================

};  //  namespace spcWAD
