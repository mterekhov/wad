#ifndef SPCWAD_ATEXTURE_H
#define SPCWAD_ATEXTURE_H

//=============================================================================

#include <vector>
#include <string>

#include "types.h"
#include "aimagedata.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
 Texture is used for walls only, for vertical surfaces only. Every texture is made of list of patches. But the texture does not contains all the patch, only it's chunk. So patchesDescriptionList is the description of what chunk of patch and where should be places
 */
class ATexture
{
public:
    ATexture(const TPatchesDescriptionList& patchesDescriptionList, const std::string& incomingName, const int incomingWidth, const int incomingHeight);
	ATexture(const ATexture& texture);
    ~ATexture();
	ATexture& operator=(const ATexture& rv);

	bool saveTextureIntoTga(const std::string& fileName);
	std::string textureName() const;

private:
    std::string _textureName;
    AImageData _imageData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ATEXTURE_H
