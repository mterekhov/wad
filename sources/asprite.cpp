#include <string>

#include "asprite.h"
#include "apalete.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ASprite::ASprite(const std::string& prefix) : spritesPrefix(prefix)
{
}

//=============================================================================

ASprite::ASprite(const ASprite& sprite) : picturesList(sprite.picturesList), spritesPrefix(sprite.spritesPrefix)
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

	spritesPrefix = rv.spritesPrefix;
	picturesList = rv.picturesList;

	return *this;
}

//=============================================================================

};  //  namespace spcWAD
