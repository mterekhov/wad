#include "atexture.h"
#include "apatch.h"

#include <stdlib.h>

//=============================================================================

namespace spcWAD
{

//=============================================================================

ATexture::ATexture(const TPatchesList& patchesList, const TLumpsList& lumpsList, const std::string& incomingName, const int incomingWidth, const int incomingHeight, const TPatchesDescriptionList& patchesDescriptionList) : _textureData(0), _textureWidth(incomingWidth), _textureHeight(incomingHeight), _textureName(incomingName)
{
	_textureData = generateTexture(patchesList, lumpsList, incomingWidth, incomingHeight, patchesDescriptionList);
}

//=============================================================================

ATexture::ATexture(const ATexture& texture) : _textureData(0), _textureWidth(texture._textureWidth), _textureHeight(texture._textureHeight)
{
	if (texture._textureWidth)
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
	
	if (_textureData && _textureWidth)
	{
		delete [] _textureData;
		_textureWidth = 0;
	}
	
	_textureName = rv._textureName;
	_textureHeight = rv._textureHeight;
	_textureWidth = rv._textureWidth;
	_textureData = new unsigned char[rv.textureDataSize()];
	memcpy(_textureData, rv._textureData, rv.textureDataSize());
	
	return *this;
}

//=============================================================================

int ATexture::textureDataSize() const
{
	return 3 * _textureHeight * _textureWidth;
}

//=============================================================================

unsigned char* ATexture::generateTexture(const TPatchesList& patchesList, const TLumpsList& lumpsList, const int incomingWidth, const int incomingHeight, const TPatchesDescriptionList& patchesDescriptionList)
{
	int textureSize = incomingHeight * incomingWidth * 3;
	if (textureSize == 0)
	{
		return 0;
	}
	
	unsigned char* textureData = new unsigned char[textureSize];
	for (TPatchesDescriptionListConstIter iter = patchesDescriptionList.begin(); iter < patchesDescriptionList.end(); iter++)
	{
		const SPatchDescription& patchDescription = *iter;
		const APatch& patch = patchesList[patchDescription.index];
		
	}
	
	return textureData;
}

//=============================================================================

};  //  namespace spcWAD
