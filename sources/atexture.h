#ifndef SPCWAD_ATEXTURE_H
#define SPCWAD_ATEXTURE_H

//=============================================================================

#include <vector>
#include <string>

#include "types.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

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
    unsigned char* _textureData;
    std::string _textureName;
    int _textureWidth;
    int _textureHeight;
	
	int textureDataSize() const;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ATEXTURE_H
