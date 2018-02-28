#include "apatch.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

APatch::APatch(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_PATCHES),
                                    m_width(0), m_height(0), m_pData(0)
{
}

//=============================================================================

APatch::~APatch()
{
    apDestroy();
}

//=============================================================================

bool APatch::apReadData(const ALump& lump, APalete& palete, FILE* wadFile)
{
    int pushOffset = ftell(wadFile);
    fseek(wadFile, alOffset(), SEEK_SET);

    //  Get image description
    if (fread(&m_width, 2, 1, wadFile) != 1)
        return false;
    if (fread(&m_height, 2, 1, wadFile) != 1)
        return false;
    if (fread(&m_xoffset, 2, 1, wadFile) != 1)
        return false;
    if (fread(&m_yoffset, 2, 1, wadFile) != 1)
        return false;

    //  Get columns of image
    int* columnOffsets = new int[m_width];
    memset(columnOffsets, 0, 4 * m_width);
    for (int i = 0; i < m_width; i++)
    {
        if (fread(&columnOffsets[i], 4, 1, wadFile) != 1)
            return false;
        columnOffsets[i] += lump.alOffset();
    }

    //  prepare data chunk
    m_pData = new unsigned char[m_width * m_height * 3];
    memset(m_pData, 0, m_width * m_height * 3);

    unsigned char terminator = 0;
    //  read and convert image data
    for (int i = 0; i < m_width; i++)
    //for (int i = m_width - 1; i >= 0; i--)
    {
        fseek(wadFile, columnOffsets[i], SEEK_SET);

        while(true)
        {
            int rowNumber = 0;
            int rowSize = 0;
            if (fread(&rowNumber, 1, 1, wadFile) != 1)
                return false;
            if (fread(&rowSize, 1, 1, wadFile) != 1)
                return false;
            fseek(wadFile, 1, SEEK_CUR);    //  read reserved byte

            unsigned char* data = new unsigned char[rowSize];
            if (fread(data, rowSize, 1, wadFile) != 1)
                return false;
            for (int j = 0; j < rowSize; j++)
            {
                int index = 3 * ((m_height - (rowNumber + j + 1)) * m_width + i);
                m_pData[index] = palete.apRed(data[j]);
                m_pData[index + 1] = palete.apGreen(data[j]);
                m_pData[index + 2] = palete.apBlue(data[j]);
            }
            delete [] data;

            fseek(wadFile, 1, SEEK_CUR);    //  read reserved byte

            if (fread(&terminator, 1, 1, wadFile) != 1)
                return false;
            if (terminator == 0xFF)
                break;

            fseek(wadFile, -1, SEEK_CUR);
        }
    }

    fseek(wadFile, pushOffset, SEEK_SET);
    m_used = true;

    //  flip over data
    unsigned char* tmp = new unsigned char[3 * m_width];
    for (int i = 0; i < m_height / 2; i++)
    {
        memcpy(tmp, &m_pData[3 * i * m_width], 3 * m_width);
        memcpy(&m_pData[3 * i * m_width], &m_pData[3 * (m_height - i - 1) * m_width], 3 * m_width);
        memcpy(&m_pData[3 * (m_height - i - 1) * m_width], tmp, 3 * m_width);
    }
    delete [] tmp;

    return true;
}

//=============================================================================

const unsigned char* APatch::apData() const
{
    return m_pData;
}

//=============================================================================

void APatch::apDestroy()
{
    if (m_pData)
    {
        delete m_pData;
        m_pData = 0;
    }
}

//=============================================================================

const int APatch::apWidth() const
{
    return m_width;
}

//=============================================================================

const int APatch::apHeight() const
{
    return m_height;
}

//=============================================================================

};  //  namespace spcWAD
