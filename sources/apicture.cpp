#include "apicture.h"
#include "apalete.h"
#include "atgaexporter.h"
#include "types.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

APicture::APicture() : _patchData(0), _patchName(""), _patchWidth(0), _patchHeight(0)
{
    
}

//=============================================================================

APicture::APicture(const unsigned char* incomingData, const std::string& incomingName, const APalete& palete) : _patchData(0), _patchName(incomingName), _patchHeight(0), _patchWidth(0)
{
	if (incomingData)
	{
		int bytesOffset = 0;
		memcpy(&_patchWidth, &incomingData[bytesOffset], 2);
		bytesOffset += 2;
		memcpy(&_patchHeight, &incomingData[bytesOffset], 2);
		bytesOffset += 2;

		bytesOffset += 4;	//	skiping offsets
		_patchData = convertData(incomingData, palete, bytesOffset);
    }
}

//=============================================================================

APicture::APicture(const APicture& patch) : _patchData(0), _patchWidth(patch._patchWidth), _patchHeight(patch._patchHeight), _patchName(patch._patchName)
{
	if (patch.patchDataSize())
	{
		_patchData = new unsigned char[patch.patchDataSize()];
		memcpy(_patchData, patch._patchData, patch.patchDataSize());
    }
}

//=============================================================================

APicture::~APicture()
{
	destroy();
}

//=============================================================================

APicture& APicture::operator=(const APicture& rv)
{
	if (this == &rv)
	{
		return *this;
	}

	destroy();
	
	_patchName = rv._patchName;
	_patchHeight = rv._patchHeight;
	_patchWidth = rv._patchWidth;
	
	_patchData = new unsigned char[rv.patchDataSize()];
	memcpy(_patchData, rv._patchData, rv.patchDataSize());
	
	return *this;
}

//=============================================================================

void APicture::destroy()
{
	if (_patchData)
	{
		delete [] _patchData;
		_patchData = 0;
		_patchHeight = 0;
		_patchWidth = 0;
		_patchName = "";
	}
}

//=============================================================================

const std::string& APicture::patchName() const
{
	return _patchName;
}

//=============================================================================

bool APicture::savePatchIntoTga(const std::string& fileName)
{
	ATGAExporter tgaExporter;
	return tgaExporter.exportData(fileName, _patchData, _patchWidth, _patchHeight);
}

//=============================================================================

const unsigned char* APicture::patchData() const
{
	return _patchData;
}

//=============================================================================

int APicture::patchDataSize() const
{
	return 3 * _patchHeight * _patchWidth;
}

//=============================================================================

int APicture::patchHeightSize() const
{
	return _patchHeight;
}

//=============================================================================

int APicture::patchWidthSize() const
{
	return _patchWidth;
}

//=============================================================================

unsigned char* APicture::convertData(const unsigned char* incomingData, const APalete& palete, const int bytesOffset)
{
	int bytesOffsetPointer = bytesOffset;

    int* columnOffsets = new int[_patchWidth];
    memset(columnOffsets, 0, 4 * _patchWidth);
    for (int i = 0; i < _patchWidth; i++)
    {
		memcpy(&columnOffsets[i], &incomingData[bytesOffsetPointer], 4);
		bytesOffsetPointer += 4;
	}

    int size = patchDataSize();
	unsigned char* convertedData = new unsigned char[size];
    memset(convertedData, PIXEL_TRANSPARENCY_MARKER, size);
    for (int i = 0; i < _patchWidth; i++)
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
                int index = 3 * ((_patchHeight - (rowNumber + j + 1)) * _patchWidth + i);
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
	
    unsigned char* tmp = new unsigned char[3 * _patchWidth];
    for (int i = 0; i < _patchHeight / 2; i++)
    {
        memcpy(tmp, &convertedData[3 * i * _patchWidth], 3 * _patchWidth);
        memcpy(&convertedData[3 * i * _patchWidth], &convertedData[3 * (_patchHeight - i - 1) * _patchWidth], 3 * _patchWidth);
        memcpy(&convertedData[3 * (_patchHeight - i - 1) * _patchWidth], tmp, 3 * _patchWidth);
    }
    delete [] tmp;

	return convertedData;
}

//=============================================================================

};  //  namespace spcWAD
