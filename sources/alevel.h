#ifndef SPCWAD_ALEVEL_H
#define SPCWAD_ALEVEL_H

//=============================================================================

#include <string>

#include "alump.h"
#include "apalete.h"
#include "types.h"
#include "athing.h"

//=============================================================================

class ALump;

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
 This class reads all the content of level and converts it in proper and modern formats
 */
class ALevel
{
public:
    ALevel();
	ALevel(FILE* wadFile, const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents, const APalete& palete);
	ALevel(const ALevel& level);
    ~ALevel();
	ALevel& operator=(const ALevel& rv);
    const TThingList& levelItemsList() const;
    const ASprite& findSprite(const AThing& thing);

private:
	TThingList _thingsList;
    TSpriteList _spritesList;

    TThingList readThings(FILE *wadFile, const ALump& lump, const TLumpsList& tableOfContents, const APalete& palete);
    void readLineDefs(FILE *wadFile, const ALump& lump, const TLumpsList& tableOfContents, const APalete& palete);

    ASprite readThingSpritesList(FILE* wadFile, const AThing& thing, const TLumpsList& tableOfContents, const APalete& palete);
	bool readLevelData(FILE* wadFile, const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents, const APalete& palete);
	TLumpsListConstIter findEndLevelLump(const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents);
	TLumpsList levelLumpsList(const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALEVEL_H
