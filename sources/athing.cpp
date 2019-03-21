#include "athing.h"
#include "autilities.h"
#include "asprite.h"
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
    {5, "BKEY"},
    {6, "YKEY"},
    {8, "BPAK"},
    {9, "SPOS"},
	{10, "play"},
	{11, "CELP"},
    {12, "play"},
    {13, "AMM1"},
	{15, "play"},
	{24, "POL5"},
    {34, "CAND"},
    {35, "CBRA"},
    {46, "TRED"},
    {48, "ELEC"},
    {58, "sarg"},
	{2001, "SHOT"},
	{2002, "MGUN"},
    {2003, "LAUN"},
    {2005, "CSAW"},
	{2007, "CLIP"},
	{2008, "SHEL"},
    {2010, "ROCK"},
    {2011, "STIM"},
    {2012, "MEDI"},
    {2013, "SOUL"},
	{2014, "BON1"},
	{2015, "BON2"},
	{2018, "ARM1"},
	{2019, "ARM2"},
    {2024, "PINS"},
    {2025, "SUIT"},
    {2026, "PMAP"},
    {2028, "COLU"},
    {2035, "bar1"},
    {2045, "PVIS"},
	{2046, "brok"},
	{2048, "ammo"},
	{2049, "SBOX"},
	{3001, "TROO"},
    {3002, "SARG"},
    {3003, "BOSS"},
    {3004, "POSS"},
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

AThing::AThing(const AThing& thing) : xPosition(thing.xPosition), yPosition(thing.yPosition), type(thing.type), angle(thing.angle), options(thing.options)
{
    
}
    
//=============================================================================

AThing& AThing::operator=(const AThing& rv)
{
    if (this == &rv)
    {
        return *this;
    }
    
    xPosition = rv.xPosition;
    yPosition = rv.yPosition;
    type = rv.type;
    angle = rv.angle;
    options = rv.options;

    return *this;
}

//=============================================================================
    
AThing::~AThing()
{
}

//=============================================================================

bool AThing::hasSprite() const
{
    if (ThingsMap[type].length() != 0)
    {
        return true;
    }
    
    return false;
}

//=============================================================================

std::string AThing::spritePrefix() const
{
    if (!hasSprite())
    {
        return "";
    }
    
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
