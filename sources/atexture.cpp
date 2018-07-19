#include "atexture.h"
#include "apatch.h"
#include "afindhelper.h"
#include "aflat.h"
#include "atgaexporter.h"

#include <stdlib.h>

//=============================================================================

namespace spcWAD
{

//=============================================================================

ATexture::ATexture(const TPatchesDescriptionList& patchesDescriptionList, const std::string& incomingName, const int incomingWidth, const int incomingHeight) : _textureData(0), _textureWidth(incomingWidth), _textureHeight(incomingHeight), _textureName(incomingName)
{
	int textureSize = _textureWidth * _textureHeight * 3;
	if (textureSize == 0)
	{
		return;
	}
	
	_textureData = new unsigned char[textureSize];
    memset(_textureData, 0, textureSize);
	for (TPatchesDescriptionListConstIter iter = patchesDescriptionList.begin(); iter != patchesDescriptionList.end(); iter++)
	{
		const SPatchDescription& patchDescription = *iter;
		
		const unsigned char* flatData = patchDescription.patch.patchData();
		int y_limit = patchDescription.patch.patchHeightSize();
		if (y_limit > _textureHeight)
		{
			y_limit = _textureHeight;
		}
		int x_limit = patchDescription.patch.patchWidthSize();
		if (x_limit > _textureWidth)
		{
			x_limit = _textureWidth;
		}
		for (int y = patchDescription.y_offset; y < y_limit; y++)
		{
			for (int x = patchDescription.x_offset; x < x_limit; x++)
			{
				int texturePixelIndex = 3 * (_textureHeight * y + x);
				int patchPixelIndex = 3 * ((y - patchDescription.y_offset) * patchDescription.patch.patchWidthSize() + x - patchDescription.x_offset);
				memcpy(&_textureData[texturePixelIndex], &flatData[patchPixelIndex], 3);
			}
		}
	}
}

//=============================================================================

ATexture::ATexture(const ATexture& texture) : _textureData(0), _textureWidth(texture._textureWidth), _textureHeight(texture._textureHeight)
{
	if (texture.textureDataSize())
	{
		int dataSize = textureDataSize();
		_textureData = new unsigned char[dataSize];
		memcpy(_textureData, texture._textureData, dataSize);
    }
}

//=============================================================================

ATexture::~ATexture()
{
	if (textureDataSize())
	{
		_textureWidth = 0;
		delete [] _textureData;
	}
}

//=============================================================================

ATexture& ATexture::operator=(const ATexture& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	if (_textureData && textureDataSize())
	{
		delete [] _textureData;
		_textureWidth = 0;
		_textureHeight = 0;
	}
	
	_textureName = rv._textureName;
	_textureHeight = rv._textureHeight;
	_textureWidth = rv._textureWidth;
	_textureData = new unsigned char[rv.textureDataSize()];
	memcpy(_textureData, rv._textureData, rv.textureDataSize());
	
	return *this;
}

//=============================================================================

std::string ATexture::textureName() const
{
	return _textureName;
}

//=============================================================================

bool ATexture::saveTextureIntoTga(const std::string& fileName)
{
	ATGAExporter tgaExporter;
	return tgaExporter.exportData(fileName, _textureData, _textureWidth, _textureHeight);
}

//=============================================================================

int ATexture::textureDataSize() const
{
	return 3 * _textureHeight * _textureWidth;
}

//=============================================================================

};  //  namespace spcWAD
