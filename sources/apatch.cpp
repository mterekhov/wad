#include "apatch.h"
#include "atgaexporter.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

APatch::APatch(const AFlat& flat, const int width, const int height, const int x_offset, const int y_offset) : _patchData(0), _patchSize(0)
{
	_patchSize = 3 * width * height;
	_patchData = new unsigned char [_patchSize];
	unsigned char* flatData = flat.flatData();
	for (int y = y_offset; y < y_offset + height; y++)
	{
		for (int x = x_offset; x < x_offset + width; x++)
		{
			_patchData[3 * width * (y - y_offset) + 3 * (x - x_offset)] = flatData[3 * width * y + 3 * x];
			_patchData[3 * width * (y - y_offset) + 3 * (x - x_offset) + 1] = flatData[3 * width * y + 3 * x + 1];
			_patchData[3 * width * (y - y_offset) + 3 * (x - x_offset) + 2] = flatData[3 * width * y + 3 * x + 2];
		}
	}
	
	ATGAExporter tgaExporter;
	tgaExporter.exportData("/Users/michael/Pictures/saved/patch.tga", _patchData, width, height);
}

//=============================================================================

APatch::APatch(const APatch& patch) : _patchData(0), _patchSize(patch._patchSize)
{
	if (patch._patchSize)
	{
		_patchData = new unsigned char[patch._patchSize];
		memcpy(_patchData, patch._patchData, patch._patchSize);
    }
}

//=============================================================================

APatch::~APatch()
{
	if (_patchSize)
	{
		_patchSize = 0;
		delete [] _patchData;
	}
}

//=============================================================================

APatch& APatch::operator=(const APatch& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	if (_patchData && _patchSize)
	{
		delete [] _patchData;
		_patchSize = 0;
	}
	
	_patchSize = rv._patchSize;
	_patchData = new unsigned char[rv._patchSize];
	
	memcpy(_patchData, rv._patchData, rv._patchSize);
	
	return *this;
}

//=============================================================================

};  //  namespace spcWAD
