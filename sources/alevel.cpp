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
    
    _levelIntegrity = 0;
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
	TLumpsList levelContent = levelLumpsList(levelLumpIter, tableOfContents);
    int integr = 0;

    ALevelIntegrity integrity;
    for (TLumpsListConstIter iter = levelContent.begin(); iter != levelContent.end(); iter++)
	{
        printf("%s\n", iter->lumpName.c_str());
        integr = integrity.appendIntegrity(integr, iter->lumpName);
        if (integrity.checkIntegrity(integr))
        {
            break;
        }

        //	This section describes all the things which are positioned on level
        if (AUtilities::stringCompare(iter->lumpName, "things"))
        {
            _thingsList = readThings(wadFile, *iter);
        }
	}
    printf("=======================================================\n");

	for (TThingList::iterator iter = _thingsList.begin(); iter != _thingsList.end(); iter++)
	{
		if (iter->name().length() == 0)
		{
			continue;
		}
		printf("<<<<<<<%s>>>>>>>\n", iter->name().c_str());
		_spritesList.push_back(readThingSprite(wadFile, *iter, tableOfContents, palete));
		printf("=======================================================\n");
	}
	
	return true;
}

//=============================================================================

ASprite ALevel::readThingSprite(FILE* wadFile, const AThing& thing, const TLumpsList& tableOfContents, const APalete& palete)
{
	TLumpsList spriteslumpList = AUtilities::findLumpsList(thing.name(), tableOfContents);
	int c = 0;
	ASprite newSprite(thing.name());
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
		newSprite.picturesList.push_back(newSpritePicture);
		std::string path = "/Users/michael/Pictures/level/";
        path += spriteLump.lumpName;
		path += ".tga";
		newSpritePicture.savePatchIntoTga(path);

		delete [] spriteData;
		
		printf("\t\t\t\t%i. sprite <%s>\n", ++c, spriteLump.lumpName.c_str());
	}

	return newSprite;
}

//=============================================================================

TThingList ALevel::readThings(FILE *wadFile, const ALump& lump)
{
	unsigned char *thingsData = new unsigned char[lump.lumpSize];
	AUtilities::readLumpData(wadFile, lump, thingsData);
	
	int byteOffset = 0;
	TThingList thingsList;
	while (byteOffset < lump.lumpSize)
	{
		AThing newThing(&thingsData[byteOffset]);
		thingsList.push_back(newThing);
		byteOffset += 10;
	}
	
	delete [] thingsData;
	return AThing::checkThingUnique(thingsList);
}

//=============================================================================

TLumpsList ALevel::levelLumpsList(const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents)
{
	TLumpsList levelContent;

	TLumpsListConstIter levelEndIter = findEndLevelLump(levelLumpIter, tableOfContents);
	if (levelEndIter == tableOfContents.end())
	{
		return levelContent;
	}

	TLumpsListConstIter iter = levelLumpIter;
	while (++iter != levelEndIter)
	{
		levelContent.push_back(*iter);
	}
	
	return levelContent;
}

//=============================================================================

TLumpsListConstIter ALevel::findEndLevelLump(const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents)
{
	std::list<std::string> endMarkerList = {"e1m2", "texture1"};
	
	TLumpsListConstIter iter = levelLumpIter;
	TLumpsListConstIter endIter;
	while (++iter != tableOfContents.end())
	{
		for (std::list<std::string>::iterator markerIter = endMarkerList.begin(); markerIter != endMarkerList.end(); markerIter++)
		{
			if (AUtilities::stringCompare(*markerIter, iter->lumpName))
			{
				return iter;
			}
		}
	}
	
	return tableOfContents.end();
}

//=============================================================================

void ALevel::destroy()
{
}

//=============================================================================

};  //  namespace spcWAD
