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
        if (std::find(thingsList.begin(), thingsList.end(), newThing) == thingsList.end())
        {
            if (ThingsMap[newThing.type].length() != 0)
            {
                newThing.sprite = readThingSpritesList(wadFile, newThing, tableOfContents, palete);
            }
            thingsList.push_back(newThing);
        }
        byteOffset += 10;
    }
    
    delete [] thingsData;
    
    return thingsList;
}

//=============================================================================

ASprite ALevel::readThingSpritesList(FILE* wadFile, const AThing& thing, const TLumpsList& tableOfContents, const APalete& palete)
{
    std::string spriteLumpsPrefix = ThingsMap[thing.type];
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
