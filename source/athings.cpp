#include "athings.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AThings::AThings(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_THINGS), m_pData(0)
{
}

//=============================================================================

AThings::~AThings()
{
    alDestroy(m_pData);
}

//=============================================================================

bool AThings::atReadData(FILE* wadFile)
{
    //  read raw data from file
	unsigned char* data = new unsigned char[alSize()];
	memset(data, 0, alSize());
    if (!alReadLump(wadFile, data))
        return false;

	return true;
}

//=============================================================================

const unsigned char* AThings::atData() const
{
    return m_pData;
}

//=============================================================================

};  //  namespace spcWAD
