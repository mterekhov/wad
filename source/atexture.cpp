#include "atexture.h"
#include <stdlib.h>

//=============================================================================

namespace spcWAD
{

//=============================================================================

ATexture::ATexture(const ALump& lump) : ALump(lump.alSize(), lump.alOffset(), lump.alName(), LUMPTYPES_TEXTURES),
                                        m_pData(0)
{
    m_pData = new unsigned char[lump.alSize()];
    memset(m_pData, 0, lump.alSize());
}

//=============================================================================

ATexture::~ATexture()
{
    alDestroy(m_pData);
}

//=============================================================================

bool ATexture::atReadData(const std::map<int, APatch*>& patches, FILE* wadFile)
{
    fseek(wadFile, 4, SEEK_CUR);    //  read reserved 4 bytes

    if (fread(&m_width, 4, 1, wadFile) != 1)
        return false;
    if (fread(&m_height, 4, 1, wadFile) != 1)
        return false;

    fseek(wadFile, 4, SEEK_CUR);        //  read reserved 4 bytes

    //  read number of patches for this texture
    int patchesCount = 0;
    if (fread(&patchesCount, 2, 1, wadFile) != 1)
        return false;

    //  now lets create texture out of patches chunks
    unsigned char* data = new unsigned char[m_width * m_height * 3];
    memset(data, 0, m_width * m_height * 3);
    for (int i = 0; i < patchesCount; i++)
    {
        int x_offset = 0;   //  where to place data in texture
        int y_offset = 0;   //  where to place data in texture
        int pId = 0;        //  patch id
        if (fread(&x_offset, 2, 1, wadFile) != 1)
            return false;
        if (fread(&y_offset, 2, 1, wadFile) != 1)
            return false;
        if (fread(&pId, 2, 1, wadFile) != 1)
            return false;
        fseek(wadFile, 4, SEEK_CUR);        //  read reserved 4 bytes

        std::map<int, APatch*>::const_iterator p = patches.find(pId);
        if (p == patches.end())
        {
            char buffer2[256] = {0};
            sprintf(buffer2, "can not find patch %i for texture %s\n", i, alName().c_str());
            continue;
        }
        int patchWidth = p->second->apWidth();
        int patchHeight = p->second->apHeight();
        const unsigned char* patchData = p->second->apData();

        //  add this piece of data into texture
        //=============================================================================
        //  Найдём кусочки которые лежат внутри текстуры и которые формируют её
        //  Вычислим координату x и ширину

        int pc_width = patchWidth;
        int pc_x = 0;

        if (x_offset < 0)
        {
            pc_x = abs(x_offset);
            pc_width -= abs(x_offset);
        }

        if (((x_offset + patchWidth) > m_width) && (x_offset >= 0))
            pc_width = m_width - x_offset;
        if (pc_width > m_width)
            pc_width = m_width;

        //=============================================================================
        //  Вычислим координату y и высоту
        int pc_height = patchHeight;
        int pc_y = 0;

        if (y_offset < 0)
        {
            pc_y = abs(y_offset);
            pc_height -= abs(y_offset);
        }

        if (((y_offset + patchHeight) > m_height) && (y_offset >= 0))
            pc_height = m_height - y_offset;
        if (pc_height > m_height)
            pc_height = m_height;

        //=============================================================================
        for (int k = 0; k < pc_height; k++)
        {
            for (int l = 0; l < pc_width; l++)
            {
                int xc = 0;
                int yc = 0;
                xc = pc_x + l;
                yc = (pc_y + k) * patchWidth;
                if (patchData[3 * (yc + xc)] != 1)
                {
                    data[3 * ((m_height - (y_offset + pc_y + pc_height) + k) * m_width + x_offset + pc_x + l)] = patchData[3 * (yc + xc)];
                    data[3 * ((m_height - (y_offset + pc_y + pc_height) + k) * m_width + x_offset + pc_x + l) + 1] = patchData[3 * (yc + xc) + 1];
                    data[3 * ((m_height - (y_offset + pc_y + pc_height) + k) * m_width + x_offset + pc_x + l) + 2] = patchData[3 * (yc + xc) + 2];
                }
            }
        }
    }

    return true;
}

//=============================================================================

const unsigned char* ATexture::atData() const
{
    return m_pData;
}

//=============================================================================

const int ATexture::atWidth() const
{
    return m_width;
}

//=============================================================================

const int ATexture::atHeight() const
{
    return m_height;
}

//=============================================================================

};  //  namespace spcWAD
