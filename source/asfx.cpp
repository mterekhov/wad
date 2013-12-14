#include "asfx.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ASFX::ASFX(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_SFX),
                                    m_pData(0)
{
    m_pData = new unsigned char[lump.alSize()];
    memset(m_pData, 0, lump.alSize());
}

//=============================================================================

ASFX::~ASFX()
{
    alDestroy(m_pData);
}

//=============================================================================

bool ASFX::asReadData(FILE* wadFile)
{
    //  read raw data from file
    if (!alReadLump(wadFile, m_pData))
        return false;

    m_used = true;

    return true;
}

//=============================================================================

const unsigned char* ASFX::asData() const
{
    return m_pData;
}

//=============================================================================

};  //  namespace spcWAD
