#include "alevel.h"
#include "autilities.h"
#include "asprite.h"
#include "alevelintegrity.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================
    
ALevel::ALevel(FILE* wadFile, const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents, const APalete& palete)
{
	if (levelLumpIter == tableOfContents.end())
	{
		return;
	}
    
	readLevelData(wadFile, levelLumpIter, tableOfContents, palete);
}

//=============================================================================

ALevel::ALevel(const ALevel& level)
{
}

//=============================================================================

ALevel::~ALevel()
{
	destroy();
}

//=============================================================================

ALevel& ALevel::operator=(const ALevel& rv)
{
	if (this == &rv)
	{
		return *this;
	}

	destroy();
	
	return *this;
}

//=============================================================================

bool ALevel::readLevelData(FILE* wadFile, const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents, const APalete& palete)
{
    int integrityMarker = 0;
    ALevelIntegrity integrity;
    for (TLumpsListConstIter iter = levelLumpIter; iter != tableOfContents.end(); iter++)
	{
        integrityMarker = integrity.appendIntegrity(integrityMarker, iter->lumpName);
        if (integrity.checkIntegrity(integrityMarker))
        {
            break;
        }

        //	This section describes all the things which are positioned on level
        if (AUtilities::stringCompare(iter->lumpName, "things"))
        {
            _thingsList = readThings(wadFile, *iter, tableOfContents, palete);
        }
	}
    
    int c = 0;
    printf("THINGS\n");
    for (TThingListIter iter = _thingsList.begin(); iter != _thingsList.end(); iter++)
    {
        printf("%i. <%s>\n", ++c, iter->spritePrefix().c_str());
    }
    
    c = 0;
    printf("SPRITES\n");
    for (TSpriteListIter iter = _spritesList.begin(); iter != _spritesList.end(); iter++)
    {
        printf("%i. <%s>\n", ++c, iter->spritesPrefix.c_str());
    }
    
	return true;
}

//=============================================================================

TThingList ALevel::readThings(FILE *wadFile, const ALump& lump, const TLumpsList& tableOfContents, const APalete& palete)
{
    unsigned char *thingsData = new unsigned char[lump.lumpSize];
    AUtilities::readLumpData(wadFile, lump, thingsData);
    
    int byteOffset = 0;
    TThingList thingsList;
    while (byteOffset < lump.lumpSize)
    {
        AThing newThing(&thingsData[byteOffset]);
        if (newThing.hasSprite())
        {
            TSpriteListIter existingSprite = std::find(_spritesList.begin(), _spritesList.end(), ASprite(newThing.spritePrefix()));
            if (existingSprite == _spritesList.end())
            {
                newThing.sprite = readThingSpritesList(wadFile, newThing, tableOfContents, palete);
                _spritesList.push_back(newThing.sprite);
            }
        }
        thingsList.push_back(newThing);
        byteOffset += 10;
    }
    
    delete [] thingsData;
    
    return thingsList;
}

//=============================================================================

ASprite ALevel::readThingSpritesList(FILE* wadFile, const AThing& thing, const TLumpsList& tableOfContents, const APalete& palete)
{
    std::string spriteLumpsPrefix = thing.spritePrefix();
	TLumpsList spriteslumpList = AUtilities::findLumpsList(spriteLumpsPrefix, tableOfContents);
	ASprite newSprite(spriteLumpsPrefix);
	for (TLumpsListIter iter = spriteslumpList.begin(); iter != spriteslumpList.end(); iter++)
	{
		TLumpsListConstIter spriteLumpIter = AUtilities::findLumpIter(iter->lumpName, tableOfContents);
		if (spriteLumpIter == tableOfContents.end())
		{
			continue;
		}
        const ALump& spriteLump = *spriteLumpIter;
        unsigned char *spriteData = new unsigned char [spriteLump.lumpSize];
        AUtilities::readLumpData(wadFile, spriteLump, spriteData);

        APicture newSpritePicture(spriteData, spriteLump.lumpName, palete);
        newSprite.picturesList[spriteLump.lumpName] = newSpritePicture;
        std::string path = "/Users/michael/Pictures/level/";
        path += spriteLump.lumpName;
        path += ".tga";
        newSpritePicture.savePatchIntoTga(path);

        delete [] spriteData;
	}

	return newSprite;
}

//=============================================================================

void ALevel::destroy()
{
}

//=============================================================================

};  //  namespace spcWAD
