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
//	int textureSize = incomingHeight * incomingWidth * 3;
//	if (textureSize == 0)
//	{
//		return;
//	}
//	
//	_textureData = new unsigned char[textureSize];
//    memset(_textureData, 0, textureSize);
//	for (TPatchesDescriptionListConstIter iter = patchesDescriptionList.begin(); iter < patchesDescriptionList.end(); iter++)
//	{
//		const SPatchDescription& patchDescription = *iter;
//		ALump& lump = patchDescription.patch.patchLump;
//		
//		const unsigned char* flatData = flatData();
//		for (int y = patchDescription.y_offset; y < incomingHeight; y++)
//		{
//			for (int x = patchDescription.x_offset; x < incomingWidth; x++)
//			{
//				_textureData[3 * (incomingHeight * y + x)] = flatData[3 * (y - patchDescription.y_offset + x - patchDescription.x_offset)];
//				_textureData[3 * (incomingHeight * y + x) + 1] = flatData[3 * (y - patchDescription.y_offset + x - patchDescription.x_offset) + 1];
//				_textureData[3 * (incomingHeight * y + x) + 2] = flatData[3 * (y - patchDescription.y_offset + x - patchDescription.x_offset) + 2];
//			}
//		}
//	}
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
