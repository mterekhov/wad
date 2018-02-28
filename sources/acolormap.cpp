#include "acolormap.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AColorMap::AColorMap(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_COLOR_MAP),
                                      m_pData(0)
{
    m_pData = new unsigned char[lump.alSize()];
    memset(m_pData, 0, lump.alSize());
}

//=============================================================================

AColorMap::~AColorMap()
{
    alDestroy(m_pData);
}

//=============================================================================

bool AColorMap::acReadData(FILE* wadFile)
{
    //  read raw data from file
    if (!alReadLump(wadFile, m_pData))
        return false;

    return true;
}

//=============================================================================

};  //  namespace spcWAD
