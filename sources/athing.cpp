#include "athing.h"
#include "autilities.h"
#include <string>
#include <map>

//=============================================================================

namespace spcWAD
{

//=============================================================================

std::map<int, std::string> ThingsMap =
{
	{1, "play"},
	{2, "play"},
	{3, "play"},
	{4, "play"},
	{9, "SPOS"},
	{10, "play"},
	{11, ""},
	{12, "play"},
	{15, "play"},
	{24, "POL5"},
	{35, "CBRA"},
	{48, "ELEC"},
	{2001, "SHOT"},
	{2002, "MGUN"},
	{2003, "LAUN"},
	{2007, "CLIP"},
	{2008, "SHEL"},
	{2011, "STIM"},
	{2012, "MEDI"},
	{2014, "BON1"},
	{2015, "BON2"},
	{2018, "ARM1"},
	{2019, "ARM2"},
	{2028, "COLU"},
	{2035, "bar1"},
	{2046, "brok"},
	{2048, "ammo"},
	{2049, "SBOX"},
	{3001, "TROO"},
	{3004, "POSS"}
};

//=============================================================================

AThing::AThing(unsigned char *thingData)
{
	if (!thingData)
	{
		return;
	}
	
	int bytesOffset = 0;
	memcpy(&xPosition, &thingData[bytesOffset], 2);
	bytesOffset += 2;
	memcpy(&yPosition, &thingData[bytesOffset], 2);
	bytesOffset += 2;
	memcpy(&angle, &thingData[bytesOffset], 2);
	bytesOffset += 2;
	memcpy(&type, &thingData[bytesOffset], 2);
	bytesOffset += 2;
	memcpy(&options, &thingData[bytesOffset], 2);
}

//=============================================================================

AThing::~AThing()
{
}

//=============================================================================

std::string AThing::name() const
{
	return ThingsMap[type];
}

//=============================================================================

TThingList AThing::checkThingUnique(const TThingList& thingsList)
{
	TThingList thingsListSorted(thingsList);
	
	//	sort by type
	std::sort(thingsListSorted.begin(), thingsListSorted.end());
	
	//	delete doubles
	thingsListSorted.erase(std::unique(thingsListSorted.begin(), thingsListSorted.end()) , thingsListSorted.end());
	
	return thingsListSorted;
}

//=============================================================================

bool AThing::operator ==(const AThing & obj) const
{
	if (type == obj.type)
	{
		return true;
	}

	return false;
}

//=============================================================================

bool AThing::operator <(const AThing & obj) const
{
	if (type < obj.type)
	{
		return true;
	}

	return false;
}

//=============================================================================

};  //  namespace spcWAD
