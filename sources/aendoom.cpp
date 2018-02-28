#include "aendoom.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AEnDoom::AEnDoom(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_ENDOOM),
                                      m_pData(0)
{
    m_pData = new unsigned char[lump.alSize()];
    memset(m_pData, 0, lump.alSize());
}

//=============================================================================

AEnDoom::~AEnDoom()
{
    alDestroy(m_pData);
}

//=============================================================================

bool AEnDoom::aeReadData(FILE* wadFile)
{
    //  read raw data from file
    if (!alReadLump(wadFile, m_pData))
        return false;

    return true;
}

//=============================================================================

};  //  namespace spcWAD
