#include "alevel.h"
#include "autilities.h"
#include "asprite.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================
    
std::vector<std::string> LevelIntegrityLumps =
{
    "THINGS",
    "LINEDEFS",
    "SIDEDEFS",
    "VERTEXES",
    "SEGS",
    "SSECTORS",
    "NODES",
    "SECTORS",
    "REJECT",
    "BLOCKMAP",
};
//THINGS
//LINEDEFS
//SIDEDEFS
//VERTEXES
//SEGS
//SSECTORS
//NODES
//SECTORS
//REJECT
//BLOCKMAP
enum ALevelIntegrity
{
    ALEVELINTEGRITY_THINGS = 1,
    ALEVELINTEGRITY_LINEDEFS = 1 << 1,
    ALEVELINTEGRITY_SIDEDEFS = 1 << 2,
    ALEVELINTEGRITY_VERTEXES = 1 << 3,
    ALEVELINTEGRITY_SEGS = 1 << 4,
    ALEVELINTEGRITY_SSECTORS = 1 << 5,
    ALEVELINTEGRITY_NODES = 1 << 6,
    ALEVELINTEGRITY_SECTORS = 1 << 7,
    ALEVELINTEGRITY_REJECT = 1 << 8,
    ALEVELINTEGRITY_BLOCKMAP = 1 << 9,
    
    ALEVELINTEGRITY_COMPLETE = ALEVELINTEGRITY_THINGS\
    | ALEVELINTEGRITY_LINEDEFS\
    | ALEVELINTEGRITY_SIDEDEFS\
    | ALEVELINTEGRITY_VERTEXES\
    | ALEVELINTEGRITY_SEGS\
    | ALEVELINTEGRITY_SSECTORS\
    | ALEVELINTEGRITY_NODES\
    | ALEVELINTEGRITY_SECTORS\
    | ALEVELINTEGRITY_REJECT\
    | ALEVELINTEGRITY_BLOCKMAP
};
    
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

    //THINGS
    //LINEDEFS
    //SIDEDEFS
    //VERTEXES
    //SEGS
    //SSECTORS
    //NODES
    //SECTORS
    //REJECT
    //BLOCKMAP

//        ALEVELINTEGRITY_THINGS = 1,
//        ALEVELINTEGRITY_LINEDEFS = 1 << 1,
//        ALEVELINTEGRITY_SIDEDEFS = 1 << 2,
//        ALEVELINTEGRITY_VERTEXES = 1 << 3,
//        ALEVELINTEGRITY_SEGS = 1 << 4,
//        ALEVELINTEGRITY_SSECTORS = 1 << 5,
//        ALEVELINTEGRITY_NODES = 1 << 6,
//        ALEVELINTEGRITY_SECTORS = 1 << 7,
//        ALEVELINTEGRITY_REJECT = 1 << 8,
//        ALEVELINTEGRITY_BLOCKMAP = 1 << 9,
    
int ALevel::integrityEnum(const std::string& integrityString)
{
    int shifter = 1;
    for (std::vector<std::string>::iterator integrityItem = LevelIntegrityLumps.begin(); integrityItem != LevelIntegrityLumps.end(); integrityItem++)
    {
        if (AUtilities::stringCompare(integrityString, *integrityItem))
        {
            return shifter;
        }
        shifter = shifter << 1;
    }
    
    return 0;
//    if (AUtilities::stringCompare(integrityString, "things"))
//    {
//        integrityEnum = ALEVELINTEGRITY_THINGS;
//    }
//
//    if (AUtilities::stringCompare(integrityString, "LINEDEFS"))
//    {
//        integrityEnum = ALEVELINTEGRITY_LINEDEFS;
//    }
//
//    if (AUtilities::stringCompare(integrityString, "SIDEDEFS"))
//    {
//        integrityEnum = ALEVELINTEGRITY_SIDEDEFS;
//    }
//
//    if (AUtilities::stringCompare(integrityString, "VERTEXES"))
//    {
//        integrityEnum = ALEVELINTEGRITY_VERTEXES;
//    }
//
//    if (AUtilities::stringCompare(integrityString, "SEGS"))
//    {
//        integrityEnum = ALEVELINTEGRITY_SEGS;
//    }
//
//    if (AUtilities::stringCompare(integrityString, "SSECTORS"))
//    {
//        integrityEnum = ALEVELINTEGRITY_SSECTORS;
//    }
//
//    if (AUtilities::stringCompare(integrityString, "NODES"))
//    {
//        integrityEnum = ALEVELINTEGRITY_NODES;
//    }
//
//    if (AUtilities::stringCompare(integrityString, "SECTORS"))
//    {
//        integrityEnum = ALEVELINTEGRITY_SECTORS;
//    }
//
//    if (AUtilities::stringCompare(integrityString, "REJECT"))
//    {
//        integrityEnum = ALEVELINTEGRITY_REJECT;
//    }
//
//    if (AUtilities::stringCompare(integrityString, "BLOCKMAP"))
//    {
//        integrityEnum = ALEVELINTEGRITY_BLOCKMAP;
//    }
//
//    return integrityEnum;
}
    
int ALevel::appendIntegrity(int currentIntegrity, const std::string& levelLumpName)
{
    int lumpIntegrity = integrityEnum(levelLumpName);
    
    if (currentIntegrity == 0)
    {
        return lumpIntegrity;
    }
    
    return lumpIntegrity | currentIntegrity;
}

//=============================================================================

int ALevel::completeIntegrity()
{
    int shifter = 1;
    std::vector<std::string>::iterator integrityItem = LevelIntegrityLumps.begin();
    integrityItem++;
    for (;integrityItem != LevelIntegrityLumps.end(); integrityItem++)
    {
        shifter |= shifter << 1;
    }
    
    return shifter;
}

//=============================================================================
    
bool ALevel::readLevelData(FILE* wadFile, const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents, const APalete& palete)
{
	TLumpsList levelContent = levelLumpsList(levelLumpIter, tableOfContents);
    int integr = 0;
    int integrityFull = completeIntegrity();
	for (TLumpsListConstIter iter = levelContent.begin(); iter != levelContent.end(); iter++)
	{
        printf("%s\n", iter->lumpName.c_str());
        integr = appendIntegrity(integr, iter->lumpName);
        if (integr == integrityFull)
        {
            break;
        }

        //	This section describes all the things which are positioned on level
//        if (AUtilities::stringCompare(iter->lumpName, "things"))
//        {
//            _thingsList = readThings(wadFile, *iter);
//            break;
//        }
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
