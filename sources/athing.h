#ifndef SPCWAD_ATHING_H
#define SPCWAD_ATHING_H

//=============================================================================

#include <string>

#include "alump.h"
#include "apalete.h"
#include "types.h"

//=============================================================================

class ALump;

//=============================================================================

namespace spcWAD
{

//=============================================================================

class AThing
{
public:
	AThing(unsigned char *thingData);
    ~AThing();

	short xPosition;
	short yPosition;
	short angle;
	short type;
	short options;
	
	std::string name() const;
	
	static TThingList checkThingUnique(const TThingList& thingsList);
	
	bool operator ==(const AThing & obj) const;
	bool operator <(const AThing & obj) const;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ATHING_H
