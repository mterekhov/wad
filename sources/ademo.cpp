#include "ademo.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ADemo::ADemo(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_DEMO),
                                      m_pData(0)
{
    m_pData = new unsigned char[lump.alSize()];
    memset(m_pData, 0, lump.alSize());
}

//=============================================================================

ADemo::~ADemo()
{
    alDestroy(m_pData);
}

//=============================================================================

bool ADemo::adReadData(FILE* wadFile)
{
    //  read raw data from file
    if (!alReadLump(wadFile, m_pData))
        return false;

    return true;
}

//=============================================================================

};  //  namespace spcWAD
