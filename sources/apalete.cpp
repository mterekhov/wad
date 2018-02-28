#include "apalete.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

APalete::APalete(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_PALETE),
                                      m_pData(0)
{
    m_pData = new unsigned char[lump.alSize()];
    memset(m_pData, 0, lump.alSize());
}

//=============================================================================

APalete::~APalete()
{
    alDestroy(m_pData);
}

//=============================================================================

bool APalete::apReadData(FILE* wadFile)
{
    //  read raw data from file
    if (!alReadLump(wadFile, m_pData))
        return false;

    return true;
}

//=============================================================================

const unsigned char APalete::apRed(const int index) const
{
    if (!m_pData)
        return 0;

    return m_pData[3 * index];
}

//=============================================================================

const unsigned char APalete::apGreen(const int index) const
{
    if (!m_pData)
        return 0;

    return m_pData[3 * index + 1];
}

//=============================================================================

const unsigned char APalete::apBlue(const int index) const
{
    if (!m_pData)
        return 0;

    return m_pData[3 * index + 2];
}

//=============================================================================

};  //  namespace spcWAD
