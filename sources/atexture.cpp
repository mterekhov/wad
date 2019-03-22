#include "atexture.h"
#include "autilities.h"
#include "aflat.h"
#include "atgaexporter.h"
#include "apicture.h"

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

		//	Соотнесем размер патча и размер текстуры в которую суем его
		//	Ну чтобы не получилось что патч больше текстуры по размерам
		int patchChunkHeight = patchDescription.patch.imageData.height();	//	Это как раз та высота которую мы должны выкусить из патча
		int patchChunkWidth = patchDescription.patch.imageData.width();

		int injectionY = patchDescription.y_offset;	//	это позиция внутри текстуры в которую надо впихать патч
		int patchY = 0;	//	это позиция внутри патча начиная с которой будем выкусывать кусочек патча
		if (injectionY < 0)
		{
			injectionY = 0;
			patchY = abs(patchDescription.y_offset);
			patchChunkHeight = patchDescription.patch.imageData.height() - patchY;
		}
		if (injectionY + patchChunkHeight > _textureHeight)
		{
			patchChunkHeight = _textureHeight - injectionY;
		}

		int injectionX = patchDescription.x_offset;	//	это позиция внутри текстуры в которую надо впихать патч
		int patchX = 0;	//	это позиция внутри патча начиная с которой будем выкусывать кусочек патча
		if (injectionX < 0)
		{
			injectionX = 0;
			patchX = abs(patchDescription.x_offset);
			patchChunkWidth = patchDescription.patch.imageData.width() - patchX;
		}
		if (injectionX + patchChunkWidth > _textureWidth)
		{
			patchChunkWidth = _textureWidth - injectionX;
		}

		const unsigned char* flatData = patchDescription.patch.imageData.data();
		for (int y = injectionY; y < injectionY + patchChunkHeight; y++)
		{
			for (int x = injectionX; x < injectionX + patchChunkWidth; x++)
			{
				int patchPixelIndexX = patchX + x - injectionX;
				int patchPixelIndexY = patchY + y - injectionY;
				int patchPixelIndex = patchPixelIndexY * patchDescription.patch.imageData.width() + patchPixelIndexX;
				int texturePixelIndex = _textureWidth * y + x;
				if (flatData[3 * patchPixelIndex] == PIXEL_TRANSPARENCY_MARKER)
				{
					continue;
				}
				memcpy(&_textureData[3 * texturePixelIndex], &flatData[3 * patchPixelIndex], 3);
			}
		}
	}
}

//=============================================================================

ATexture::ATexture(const ATexture& texture) : _textureData(0), _textureWidth(texture._textureWidth), _textureHeight(texture._textureHeight), _textureName(texture.textureName())
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
