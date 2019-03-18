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

class ALevel
{
public:
	ALevel(FILE* wadFile, const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents, const APalete& palete);
	ALevel(const ALevel& level);
    ~ALevel();
	ALevel& operator=(const ALevel& rv);

private:
	TThingList _thingsList;
	TSpriteList _spritesList;

	ASprite readThingSprite(FILE* wadFile, const AThing& thing, const TLumpsList& tableOfContents, const APalete& palete);
	TThingList readThings(FILE *wadFile, const ALump& lump);
	void destroy();
	bool readLevelData(FILE* wadFile, const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents, const APalete& palete);
	TLumpsListConstIter findEndLevelLump(const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents);
	TLumpsList levelLumpsList(const TLumpsListConstIter& levelLumpIter, const TLumpsList& tableOfContents);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALEVEL_H
