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

ATexture::ATexture(const TPatchesDescriptionList& patchesDescriptionList, const std::string& incomingName, const int incomingWidth, const int incomingHeight) : _imageData(incomingWidth, incomingHeight), _textureName(incomingName)
{
    unsigned char *textureData = _imageData.data();
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
		if (injectionY + patchChunkHeight > _imageData.height())
		{
			patchChunkHeight = _imageData.height() - injectionY;
		}

		int injectionX = patchDescription.x_offset;	//	это позиция внутри текстуры в которую надо впихать патч
		int patchX = 0;	//	это позиция внутри патча начиная с которой будем выкусывать кусочек патча
		if (injectionX < 0)
		{
			injectionX = 0;
			patchX = abs(patchDescription.x_offset);
			patchChunkWidth = patchDescription.patch.imageData.width() - patchX;
		}
		if (injectionX + patchChunkWidth > _imageData.width())
		{
			patchChunkWidth = _imageData.width() - injectionX;
		}

		const unsigned char* flatData = patchDescription.patch.imageData.data();
		for (int y = injectionY; y < injectionY + patchChunkHeight; y++)
		{
			for (int x = injectionX; x < injectionX + patchChunkWidth; x++)
			{
				int patchPixelIndexX = patchX + x - injectionX;
				int patchPixelIndexY = patchY + y - injectionY;
				int patchPixelIndex = patchPixelIndexY * patchDescription.patch.imageData.width() + patchPixelIndexX;
				int texturePixelIndex = _imageData.width() * y + x;
				if (flatData[3 * patchPixelIndex] == PIXEL_TRANSPARENCY_MARKER)
				{
					continue;
				}
				memcpy(&textureData[3 * texturePixelIndex], &flatData[3 * patchPixelIndex], 3);
			}
		}
	}
}

//=============================================================================

ATexture::ATexture(const ATexture& texture) : _imageData(texture._imageData), _textureName(texture._textureName)
{
}

//=============================================================================

ATexture::~ATexture()
{
}

//=============================================================================

ATexture& ATexture::operator=(const ATexture& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	_textureName = rv._textureName;
    _imageData = rv._imageData;
    
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
    return _imageData.exportIntoTga(fileName);
}

//=============================================================================

};  //  namespace spcWAD
