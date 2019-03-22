#ifndef SPCWAD_ATHING_H
#define SPCWAD_ATHING_H

//=============================================================================

#include <string>
#include <map>

#include "types.h"
#include "asprite.h"

//=============================================================================

class ASprite;

//=============================================================================

namespace spcWAD
{

//=============================================================================

extern std::map<int, std::string> ThingsMap;

/**
 Thing is the items you can see and can not see on map
 */
class AThing
{
public:
	AThing(unsigned char *thingData);
    AThing(const AThing& thing);
    ~AThing();

	short xPosition;
	short yPosition;
	short angle;
	short type;
	short options;

	static TThingList checkThingUnique(const TThingList& thingsList);
    
    bool hasSprite() const;
    std::string spritePrefix() const;
	
	bool operator ==(const AThing & obj) const;
	bool operator <(const AThing & obj) const;
    AThing& operator=(const AThing& rv);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ATHING_H
