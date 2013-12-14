#include "awad.h"
#include "aflat.h"
#include "apalete.h"
#include "apatch.h"
#include "atexture.h"
#include <stdio.h>

//=============================================================================

namespace spcWAD
{

//=============================================================================
    
#pragma mark - Constructor&Destructor -
    
//=============================================================================

AWAD::AWAD(const std::string& fileName) : m_type(WADTYPE_UNKNOWN), m_fileName(fileName)
{
    FILE* wadFile = awOpen(fileName);
    if (!wadFile)
        throw;

    if (!awCheckSignature(wadFile))
        throw;

    if (!awReadLumpsContent(wadFile))
        throw;

    if (!awReadPalete(wadFile))
        throw;

    if (!awReadFlats(wadFile))
        throw;

    if (!awReadPatches(wadFile))
        throw;

    if (!awReadTextures(wadFile))
        throw;

    awClose(wadFile);
}

//=============================================================================

AWAD::~AWAD()
{
    awDestroy();
}

//=============================================================================

#pragma mark - WAD file operations -
    
//=============================================================================
    
FILE* AWAD::awOpen(const std::string& fileName)
{
    FILE* wadFile = 0;
    wadFile = fopen(fileName.c_str(), "rb");
    if (!wadFile)
        return 0;

    return wadFile;
}

//=============================================================================

void AWAD::awClose(FILE* wadFile)
{
    if (wadFile)
        fclose(wadFile);
}

//=============================================================================

bool AWAD::awCheckSignature(FILE* wadFile)
{
    char magic[4] = {0};
    int read = fread(magic, 1, 4, wadFile);
    if (read != 4)
        return false;

    if (!strncmp(magic, "IWAD", 4))
        m_type = WADTYPE_INTERNAL_WAD;

    if (!strncmp(magic, "PWAD", 4))
        m_type = WADTYPE_PATCH_WAD;

    return true;
}

//=============================================================================

const std::string& AWAD::awFileName() const
{
    return m_fileName;
}

//=============================================================================

#pragma mark - Readers -
    
//=============================================================================
    
bool AWAD::awReadLumpsContent(FILE* wadFile)
{
    int lumpsNumber = 0;
    int read = fread(&lumpsNumber, 4, 1, wadFile);
    if (read != 1)
        return false;

    int lumpsTOCOffset = 0;
    read = fread(&lumpsTOCOffset, 4, 1, wadFile);
    if (read != 1)
        return false;

    if (fseek(wadFile, lumpsTOCOffset, SEEK_SET))
        return false;

    ALump* newLump = 0;
    for (int i = 0; i < lumpsNumber; i++)
    {
        int offset = 0;
        //  read offset
        read = fread(&offset, 4, 1, wadFile);
        if (read != 1)
            return false;

        //  read size of lump
        int size = 0;
        read = fread(&size, 4, 1, wadFile);
        if (read != 1)
            return false;

        //  read name of lump
        char buffer[9] = {0};
        read = fread(&buffer, 8, 1, wadFile);
        if (read != 1)
            return false;

        newLump = new ALump(size, offset, buffer);
        m_lumps.push_back(newLump);
    }

    return true;
}

//=============================================================================

bool AWAD::awReadPalete(FILE* wadFile)
{
    TSeqIter iter = awFindLump("PLAYPAL");
    if (fseek(wadFile, (*iter)->alOffset(), SEEK_SET))
        return false;

    APalete* palete = new APalete(*(*iter));
    if (!palete->apReadData(wadFile))
        return false;

    *iter = palete;

    return true;
}

//=============================================================================

bool AWAD::awReadFlats(FILE* wadFile)
{
    //  read first part of flats
    TSeqIter f1_start = awFindLump("F1_START");
    TSeqIter f1_end = awFindLump("F1_END");
    if (!awReadFlatRange(wadFile, f1_start, f1_end))
        return false;

    //  read second part of flats
    TSeqIter f2_start = awFindLump("F2_START");
    TSeqIter f2_end = awFindLump("F2_END");
    if (!awReadFlatRange(wadFile, f2_start, f2_end))
        return false;

    return true;
}

//=============================================================================

bool AWAD::awReadFlatRange(FILE* wadFile, TSeqIter iter, TSeqIter iter_end)
{
    TSeqIter iter_err = m_lumps.end();
    if ((iter != iter_err) && (iter_end != iter_err))
    {
        APalete* palete = static_cast<APalete*>(*awFindLump("PLAYPAL"));
        ++iter;
        AFlat* newFlat = 0;
        while (iter != iter_end)
        {
            newFlat = new AFlat(*(*iter));
            if (!newFlat->afReadData(*palete, wadFile))
                return false;

            *iter = newFlat;
            ++iter;
        }
    }

    return true;
}

//=============================================================================

bool AWAD::awReadPatches(FILE* wadFile)
{
    APalete* palete = static_cast<APalete*>(*awFindLump("PLAYPAL"));

    TSeqIter pNames = awFindLump("PNAMES");
    fseek(wadFile, (*pNames)->alOffset(), SEEK_SET);
    int pCount = 0;
    if (fread(&pCount, 4, 1, wadFile) != 1)
        return false;

    //  read the names of lumps which are patches
    APatch* newPatch = 0;
    for (int i = 0; i < pCount; i++)
    {
        unsigned char name[9] = {0};
        if (fread(name, 8, 1, wadFile) != 1)
            return false;

        std::string stlstr = (char*)name;
        TSeqIter iter = awFindLump(stlstr);
        if (iter == m_lumps.end())
        {
            char buffer2[256] = {0};
            sprintf(buffer2, "%i. %s was not found in lump directory\n", i, name);
            continue;
        }

        newPatch = new APatch(*(*iter));
        newPatch->apReadData(*newPatch, *palete, wadFile);
        *iter = newPatch;
        m_patchesIndexes[i] = newPatch;
    }

    return true;
}

//=============================================================================

bool AWAD::awReadTextures(FILE* wadFile)
{
    TSeqIter pTex = awFindLump("TEXTURE1");
    fseek(wadFile, (*pTex)->alOffset(), SEEK_SET);
    int tCount = 0;
    if (fread(&tCount, 4, 1, wadFile) != 1)
        return false;

    ATexture* newTexture = 0;
    int tOffset = 0;
    for (int i = 0; i < tCount; i++)
    {
        if (fread(&tOffset, 4, 1, wadFile) != 1)
            return false;
        tOffset += (*pTex)->alOffset();
        int pushOffset = fseek(wadFile, tOffset, SEEK_SET);

        unsigned char name[9] = {0};
        if (fread(name, 8, 1, wadFile) != 1)
            return false;

        std::string stlstr = (char*)name;
        TSeqIter iter = awFindLump(stlstr);
        if (iter == m_lumps.end())
        {
            char buffer2[256] = {0};
            sprintf(buffer2, "%i. %s was not found in lump directory\n", i, name);
            continue;
        }

        newTexture = new ATexture(*(*iter));
        newTexture->atReadData(m_patchesIndexes, wadFile);
        *iter = newTexture;

        fseek(wadFile, pushOffset, SEEK_SET);
    }

    return true;
}

//=============================================================================

#pragma mark - Lump routine -
    
//=============================================================================

const TSequence& AWAD::awLumps() const
{
    return m_lumps;
}

//=============================================================================

TSequence& AWAD::awLumps()
{
    return m_lumps;
}

//=============================================================================

const ALump* AWAD::awGetLump(const std::string& name)
{
    TSeqIter iter = m_lumps.begin();
    TSeqIter iter_end = m_lumps.end();
    while(iter != iter_end)
    {
        if ((*iter)->alName() == name)
            return *iter;
        ++iter;
    }

    return 0;
}

//=============================================================================

TSeqIter AWAD::awFindLump(const std::string& name)
{
    TSeqIter iter = m_lumps.begin();
    TSeqIter iter_end = m_lumps.end();
    while(iter != iter_end)
    {
        if ((*iter)->alName() == name)
            return iter;
        ++iter;
    }

    return iter_end;
}

//=============================================================================

void AWAD::awDestroy()
{
    TSeqIter iter = m_lumps.begin();
    TSeqIter iter_end = m_lumps.end();

    while(iter != iter_end)
    {
        delete (*iter);
        ++iter;
    }

    m_lumps.clear();
    m_patchesIndexes.clear();
}

//=============================================================================

#pragma mark - Misc -
    
//=============================================================================
    
bool AWAD::awIntoTga(const std::string& fileName, const AFlat* flat)
{
	if (!flat)
		return false;

    unsigned char* data = const_cast<unsigned char*>(flat->afData());
    if (!awIntoTga(fileName, data, FLAT_WIDTH, FLAT_HEIGHT))
        return false;

	return true;
}

//=============================================================================

bool AWAD::awIntoTga(const std::string& fileName, const APatch* patch)
{
	if (!patch)
		return false;

    unsigned char* data = const_cast<unsigned char*>(patch->apData());
    if (!awIntoTga(fileName, data, patch->apWidth(), patch->apHeight()))
        return false;

	return true;
}

//=============================================================================

bool AWAD::awIntoTga(const std::string& fileName, unsigned char* data, const int width, const int height)
{
	if (!data)
		return false;

    unsigned char byte_1 = 0;
    unsigned short byte_2 = 0;
    FILE* filo = fopen(fileName.c_str(), "wb");
    if (!filo)
        return false;

    fwrite(&byte_1, 1, 1, filo); //  identity length
    fwrite(&byte_1, 1, 1, filo); //  palete type
    byte_1 = 2;
    fwrite(&byte_1, 1, 1, filo); //  image type
    byte_1 = 0;
    fwrite(&byte_2, 2, 1, filo); //  palete offset
    fwrite(&byte_2, 2, 1, filo); //  palete size
    fwrite(&byte_1, 1, 1, filo); //  palete bpp
    fwrite(&byte_2, 2, 1, filo); //  x coord
    fwrite(&byte_2, 2, 1, filo); //  y coord

    byte_2 = width;
    fwrite(&byte_2, 2, 1, filo); //  image width
    byte_2 = height;
    fwrite(&byte_2, 2, 1, filo); //  image height

    byte_1 = 24;
    fwrite(&byte_1, 1, 1, filo); //  byte per pixel
    byte_1 = 0;
    fwrite(&byte_1, 1, 1, filo); //  image property

    RGB2BGR(data, width, height);
    FlipOver(data, width, height);
    if (fwrite(data, 3 * width * height, 1, filo) != 1) //  image data
        return false;
    FlipOver(data, width, height);
    RGB2BGR(data, width, height);

    fclose(filo);

	return true;
}

//=============================================================================

bool AWAD::RGB2BGR(unsigned char* data, int width, int height)
{
    if (!data)
        return true;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = 3 * (i * width + j);
            unsigned char tmp = data[index];
            data[index] = data[index + 2];
            data[index + 2] = tmp;
        }
    }

    return true;
}

//=============================================================================

bool AWAD::FlipOver(unsigned char* data, int width, int height)
{
    if (!data)
        return true;

    unsigned char* tmp = new unsigned char[3 * width];
    for (int i = 0; i < height / 2; i++)
    {
        memcpy(tmp, &data[3 * i * width], 3 * width);
        memcpy(&data[3 * i * width], &data[3 * (height - i - 1) * width], 3 * width);
        memcpy(&data[3 * (height - i - 1) * width], tmp, 3 * width);
    }

    delete tmp;

    return true;
}

//=============================================================================

const unsigned int AWAD::awLumpsCount() const
{
    return m_lumps.size();
}

//=============================================================================

};  //  namespace spcWAD
