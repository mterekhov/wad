#ifndef SPCWAD_ASPRITE_H
#define SPCWAD_ASPRITE_H

//=============================================================================

#include <string>

#include "apicture.h"
#include "types.h"

//=============================================================================

class APalete;

//=============================================================================

namespace spcWAD
{

//=============================================================================

class ASprite
{
public:
	ASprite(const std::string& spriteName);
	ASprite(const ASprite& sprite);
    ~ASprite();
	ASprite& operator=(const ASprite& rv);

	std::string name;
	TIndexedPicturesList picturesList;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ASPRITE_H