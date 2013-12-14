#include "asfx.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ASFX::ASFX(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_FLATS),
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

bool ASFX::asReadData(APalete& palete, FILE* wadFile)
{
    //  read raw data from file
    if (!alReadLump(wadFile, m_pData))
        return false;

    //  convert paleted data into usual 24-bit image
    unsigned char* final_data = new unsigned char[FLAT_WIDTH * FLAT_HEIGHT * 3];
    memset(final_data, 0, FLAT_HEIGHT * FLAT_WIDTH * 3);
    for (int i = 0; i < FLAT_HEIGHT; i++)
    {
        for (int j = 0; j < FLAT_WIDTH; j++)
        {
            int index = m_pData[FLAT_WIDTH * i + j];
            final_data[3 * FLAT_WIDTH * i + 3 * j] = palete.apRed(index);
            final_data[3 * FLAT_WIDTH * i + 3 * j + 1] = palete.apGreen(index);
            final_data[3 * FLAT_WIDTH * i + 3 * j + 2] = palete.apBlue(index);
        }
    }

    alDestroy(m_pData);
    m_pData = final_data;
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
