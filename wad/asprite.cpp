#include <string>

#include "asprite.h"
#include "apalete.h"
#include "autilities.h"

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

bool ASprite::operator ==(const ASprite & obj) const
{
    if (AUtilities::stringCompare(spritesPrefix, obj.spritesPrefix))
    {
        return true;
    }
    
    return false;
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
