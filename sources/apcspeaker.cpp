#include "apcspeaker.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

APCSpeaker::APCSpeaker(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_PCSPEAKER),
                                    m_pData(0)
{
    m_pData = new unsigned char[lump.alSize()];
    memset(m_pData, 0, lump.alSize());
}

//=============================================================================

APCSpeaker::~APCSpeaker()
{
    alDestroy(m_pData);
}

//=============================================================================

bool APCSpeaker::apReadData(FILE* wadFile)
{
    //  read raw data from file
    if (!alReadLump(wadFile, m_pData))
        return false;

    m_used = true;

    return true;
}

//=============================================================================

const unsigned char* APCSpeaker::apData() const
{
    return m_pData;
}

//=============================================================================

};  //  namespace spcWAD
