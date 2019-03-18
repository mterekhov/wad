#include <string>

#include "asprite.h"
#include "apalete.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ASprite::ASprite(const std::string& spriteName) : name(spriteName)
{
}

//=============================================================================

ASprite::ASprite(const ASprite& sprite) : picturesList(sprite.picturesList), name(sprite.name)
{

}

//=============================================================================

ASprite::~ASprite()
{
}

//=============================================================================

ASprite& ASprite::operator=(const ASprite& rv)
{
	if (this == &rv)
	{
		return *this;
	}

	name = rv.name;
	picturesList = rv.picturesList;

	return *this;
}

//=============================================================================

};  //  namespace spcWAD
