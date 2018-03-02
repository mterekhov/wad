#include <stdio.h>

#include "awad.h"
#include "alump.h"
#include "apalete.h"
#import "aflat.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

#pragma mark - Constructor&Destructor -
    
//=============================================================================

AWAD::AWAD(const std::string& fileName) : _type(WADTYPE_UNKNOWN), _fileName(fileName), _palete(0, 0), _colorMap(0, 0), _enDoom(0, 0)
{
	FILE* wadFile = 0;
	wadFile = fopen(fileName.c_str(), "rb");
	if (!wadFile)
		throw;

	if (!checkSignature(wadFile))
        throw;

    if (!readTableOfContents(wadFile))
        throw;

	if (!readPalete(wadFile))
		throw;
	
	if (!readColorMap(wadFile))
		throw;
	
	if (!readEndDoom(wadFile))
		throw;

	if (!readDemos(wadFile))
		throw;

    if (!readFlats(wadFile))
        throw;

    if (!readPatches(wadFile))
        throw;

    if (!readTextures(wadFile))
        throw;

	//	export flats into tga
//	for (TFlatsListIter iter = _flatsList.begin(); iter < _flatsList.end(); iter++)
//	{
//		AFlat& flat = *iter;
//		std::string path = "/Users/michael/Pictures/saved/";
//		path += flat.flatName();
//		path += ".tga";
//		flat.saveFlatIntoTga(path);
//	}

//    if (!awReadTextures(wadFile))
//        throw;
//
//    if (!awReadSFX(wadFile))
//        throw;
//
//	if (!awReadPCSpeaker(wadFile))
//		throw;
//
//	if (!awReadMaps(wadFile))
//		throw;
	
	int counter = 1;
	for (TLumpsListIter iter = _tableOfContents.begin(); iter < _tableOfContents.end(); iter++)
	{
		printf("%i. %s\t%x\n", counter++, (*iter).lumpName.c_str(), (*iter).lumpOffset);
	}

	counter = 1;
	for (TPatchesListIter iter = _patchesList.begin(); iter < _patchesList.end(); iter++)
	{
		printf("%i. %s\n", counter++, (*iter).patchName.c_str());
	}

	fclose(wadFile);
}

//=============================================================================

AWAD::~AWAD()
{
}

//=============================================================================

bool AWAD::checkSignature(FILE* wadFile)
{
    char magic[4] = {0};
    int read = fread(magic, 1, 4, wadFile);
    if (read != 4)
        return false;

    if (!strncmp(magic, "IWAD", 4))
        _type = WADTYPE_INTERNAL_WAD;

    if (!strncmp(magic, "PWAD", 4))
        _type = WADTYPE_PATCH_WAD;

    return true;
}

//=============================================================================

bool AWAD::readTableOfContents(FILE* wadFile)
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
        char name[9] = {0};
        read = fread(&name, 8, 1, wadFile);
        if (read != 1)
            return false;
		ALump newLump(size, offset, name);
        _tableOfContents.push_back(newLump);
    }

    return true;
}

//=============================================================================

bool AWAD::readPalete(FILE* wadFile)
{
	ALump playpalLump = findLump("PLAYPAL");

	unsigned char *lumpData = new unsigned char [playpalLump.lumpSize];
    memset(lumpData, 0, playpalLump.lumpSize);
	
	readLumpData(wadFile, playpalLump, lumpData);
	_palete = APalete(lumpData, playpalLump.lumpSize);
	
	delete [] lumpData;

	return true;
}

//=============================================================================

bool AWAD::readColorMap(FILE* wadFile)
{
	ALump colorMapLump = findLump("COLORMAP");

	unsigned char *lumpData = new unsigned char [colorMapLump.lumpSize];
    memset(lumpData, 0, colorMapLump.lumpSize);
	
	readLumpData(wadFile, colorMapLump, lumpData);

	_colorMap = AColorMap(lumpData, colorMapLump.lumpSize);

	return true;
}

//=============================================================================

bool AWAD::readEndDoom(FILE* wadFile)
{
	ALump endoomLump = findLump("ENDOOM");

	unsigned char *lumpData = new unsigned char [endoomLump.lumpSize];
    memset(lumpData, 0, endoomLump.lumpSize);
	
	readLumpData(wadFile, endoomLump, lumpData);

	_enDoom = AEnDoom(lumpData, endoomLump.lumpSize);

	return true;
}

//=============================================================================

bool AWAD::readDemos(FILE* wadFile)
{
	TLumpsList demosList = findLumpsList("DEMO");
	for (TLumpsListIter iter = demosList.begin(); iter < demosList.end(); iter++)
	{
		ALump demoLump = findLump(iter->lumpName);
		unsigned char *lumpData = new unsigned char [demoLump.lumpSize];
		memset(lumpData, 0, demoLump.lumpSize);
		
		readLumpData(wadFile, demoLump, lumpData);

		ADemo newDemo(lumpData, demoLump.lumpSize, demoLump.lumpName);
		_demosList.push_back(newDemo);
	}

	return true;
}

//=============================================================================

bool AWAD::readFlats(FILE* wadFile)
{
    //  read first part of flats
    if (!readFlatsRange(wadFile, "F1_START", "F1_END"))
        return false;

    //  read second part of flats
    if (!readFlatsRange(wadFile, "F2_START", "F2_END"))
        return false;

    return true;
}

//=============================================================================

bool AWAD::readFlatsRange(FILE* wadFile, const std::string& beginLumpName, const std::string& endLumpName)
{
	TLumpsListIter beginLump = findLumpIter(beginLumpName);
	TLumpsListIter endLump = findLumpIter(endLumpName);
    TLumpsListIter lumpListEnd = _tableOfContents.end();
	
    if ((beginLump != lumpListEnd) && (endLump != lumpListEnd))
    {
        ++beginLump;
		for (TLumpsListIter iter = beginLump; iter < endLump; iter++)
		{
			ALump flatLump = (*iter);
			unsigned char *lumpData = new unsigned char [flatLump.lumpSize];
			memset(lumpData, 0, flatLump.lumpSize);
			
			readLumpData(wadFile, flatLump, lumpData);
			
			AFlat newFlat(lumpData, flatLump.lumpSize, flatLump.lumpName, _palete);
			_flatsList.push_back(newFlat);
		}
    }

    return true;
}

//=============================================================================

bool AWAD::readPatches(FILE* wadFile)
{
    ALump pNamesLump = findLump("PNAMES");
    fseek(wadFile, pNamesLump.lumpOffset, SEEK_SET);
    int patchesCount = 0;
    if (fread(&patchesCount, 4, 1, wadFile) != 1)
    {
        return false;
	}

    for (int i = 0; i < patchesCount; i++)
    {
        char patchName[9] = {0};
        if (fread(patchName, 8, 1, wadFile) != 1)
        {
            return false;
		}
		
		APatch newPatch(patchName, i);
		_patchesList.push_back(newPatch);
    }

    return true;
}

//=============================================================================

bool AWAD::readTextures(FILE* wadFile)
{
    ALump textureLump = findLump("TEXTURE1");
    fseek(wadFile, textureLump.lumpOffset, SEEK_SET);
    int texturesCount = 0;
    if (fread(&texturesCount, 4, 1, wadFile) != 1)
    {
        return false;
	}

	std::vector<int> texturesOffsetsList;
    for (int i = 0; i < texturesCount; i++)
    {
	    int textureOffset = 0;
        if (fread(&textureOffset, 4, 1, wadFile) != 1)
        {
            return false;
		}
        textureOffset += textureLump.lumpOffset;
		texturesOffsetsList.push_back(textureOffset);
    }

	int counter = 1;
	for (std::vector<int>::iterator iter = texturesOffsetsList.begin(); iter < texturesOffsetsList.end(); iter++)
	{
		fseek(wadFile, (*iter), SEEK_SET);
		unsigned char name[9] = {0};
		if (fread(name, 8, 1, wadFile) != 1)
		{
			return false;
		}
		
		int buffer1 = 0;
		if (fread(&buffer1, 2, 1, wadFile) != 1)
		{
			return false;
		}
		int buffer2 = 0;
		if (fread(&buffer2, 2, 1, wadFile) != 1)
		{
			return false;
		}
		int width = 0;
		if (fread(&width, 2, 1, wadFile) != 1)
		{
			return false;
		}
		int height = 0;
		if (fread(&height, 2, 1, wadFile) != 1)
		{
			return false;
		}
		int buffer3 = 0;
		if (fread(&buffer3, 2, 1, wadFile) != 1)
		{
			return false;
		}
		int buffer4 = 0;
		if (fread(&buffer4, 2, 1, wadFile) != 1)
		{
			return false;
		}
		int patchNumbers = 0;
		if (fread(&patchNumbers, 2, 1, wadFile) != 1)
		{
			return false;
		}
		printf("%i. <%s> size %ix%i patch numbers %i\n", counter++, name, width, height, patchNumbers);
		for (int patchIndex = 0; patchIndex < patchNumbers; patchIndex++)
		{
			int xOffset = 0;
			if (fread(&xOffset, 2, 1, wadFile) != 1)
			{
				return false;
			}
			int yOffset = 0;
			if (fread(&yOffset, 2, 1, wadFile) != 1)
			{
				return false;
			}
			int patchIndexInPatchDirectory = 0;
			if (fread(&patchIndexInPatchDirectory, 2, 1, wadFile) != 1)
			{
				return false;
			}
			int buffer5 = 0;
			if (fread(&buffer5, 2, 1, wadFile) != 1)
			{
				return false;
			}
			int buffer6 = 0;
			if (fread(&buffer6, 2, 1, wadFile) != 1)
			{
				return false;
			}
			printf("\t\t\tx_offset = %i, y_offset = %i, patchIndex = %i\n", xOffset, yOffset, patchIndexInPatchDirectory);
		}
	}
	
    return true;
}

//=============================================================================

#pragma mark - Lump operations -

//=============================================================================

void AWAD::readLumpData(FILE* wadFile, ALump lumpToRead, unsigned char *lumpData)
{
	if (fseek(wadFile, lumpToRead.lumpOffset, SEEK_SET))
	{
		return;
	}
	
	int read = fread(lumpData, lumpToRead.lumpSize, 1, wadFile);
	if (read != 1)
	{
		return;
	}
}

//=============================================================================

AFlat AWAD::findFlat(const std::string& flatNameToFind)
{
	for (TFlatsListIter iter = _flatsList.begin(); iter < _flatsList.end(); iter++)
	{
		if (iter->flatName() == flatNameToFind)
		{
			return (*iter);
		}
	}

	return AFlat(0, 0, "", _palete);
}

//=============================================================================

ALump AWAD::findLump(const std::string& lumpNameToFind)
{
	return *findLumpIter(lumpNameToFind);
}

//=============================================================================

TLumpsListIter AWAD::findLumpIter(const std::string& lumpNameToFind)
{
	for (TLumpsListIter iter = _tableOfContents.begin(); iter < _tableOfContents.end(); iter++)
	{
		if ((*iter).lumpName == lumpNameToFind)
			return iter;
	}

	return _tableOfContents.end();
}

//=============================================================================

TLumpsList AWAD::findLumpsList(const std::string& lumpsNameMask)
{
	TLumpsList founded;
	for (TLumpsListIter iter = _tableOfContents.begin(); iter < _tableOfContents.end(); iter++)
	{
		std::string lumpName = iter->lumpName;
		if (lumpName.compare(0, lumpsNameMask.length(), lumpsNameMask) == 0)
		{
			founded.push_back(*iter);
		}
	}

	return founded;
}

//=============================================================================

#pragma mark - TRASH -

//
//bool AWAD::awReadMaps(FILE* wadFile)
//{
//	amDefineMapLumps(wadFile);
//	int counter = 1;
//	for (TLumpsList::iterator iter = _tableOfContents.begin(); iter < _tableOfContents.end(); iter++)
//	{
//		ALump* lump = static_cast<ALump *>(*iter);
//		printf("%i. %s\t\t%i\n", counter, lump->alName().c_str(), lump->alType());
//		counter++;
//	}
//
//	return true;
//}
//
////=============================================================================
//
//bool AWAD::awReadSFX(FILE* wadFile)
//{
//    TLumpsListIter it_begin = _tableOfContents.begin();
//    TLumpsListIter it_end = _tableOfContents.end();
//
//    ASFX* newSfx = 0;
//    for (spcWAD::TLumpsListIter it = it_begin; it < it_end; it++)
//    {
//        std::string lumpName = (*it)->alName();
//        if (lumpName.find("DS") == 0)
//        {
//            newSfx = new ASFX(*(*it));
//            newSfx->asReadData(wadFile);
//            *it = newSfx;
//        }
//    }
//
//    return true;
//}
//
////=============================================================================
//
//bool AWAD::awReadPCSpeaker(FILE* wadFile)
//{
//    TLumpsListIter it_begin = _tableOfContents.begin();
//    TLumpsListIter it_end = _tableOfContents.end();
//
//    APCSpeaker* newSpeaker = 0;
//    for (spcWAD::TLumpsListIter it = it_begin; it < it_end; it++)
//    {
//        std::string lumpName = (*it)->alName();
//        if (lumpName.find("DP") == 0)
//        {
//            newSpeaker = new APCSpeaker(*(*it));
//            newSpeaker->apReadData(wadFile);
//            *it = newSpeaker;
//        }
//    }
//
//    return true;
//}
//
////=============================================================================
//
//#pragma mark - Lump routine -
//
////=============================================================================
//
//TLumpsList AWAD::awFilteredLumps(const ELumpTypes lumpType)
//{
//    TLumpsList finalVector;
//    for (spcWAD::TLumpsListIter it = _tableOfContents.begin(); it <_tableOfContents.end(); it++)
//    {
//        spcWAD::ELumpTypes type = (*it)->alType();
//        if (type == lumpType)
//            finalVector.push_back(*it);
//    }
//
//    return finalVector;
//}
//
////=============================================================================
//
//TLumpsList& AWAD::awLumps()
//{
//    return _tableOfContents;
//}
//
////=============================================================================
//
//const ALump* AWAD::awGetLump(const std::string& name)
//{
//    TLumpsListIter iter = _tableOfContents.begin();
//    TLumpsListIter iter_end = _tableOfContents.end();
//    while(iter != iter_end)
//    {
//        if ((*iter)->alName() == name)
//            return *iter;
//        ++iter;
//    }
//
//    return 0;
//}
//
////=============================================================================
//
//TLumpsListIter AWAD::awFindLump(const std::string& name)
//{
//	TLumpsListIter iter = _tableOfContents.begin();
//	TLumpsListIter iter_end = _tableOfContents.end();
//	while(iter != iter_end)
//	{
//		if ((*iter)->alName() == name)
//			return iter;
//		++iter;
//	}
//
//	return iter_end;
//}
//
////=============================================================================
//
//TLumpsList AWAD::awFindZeroSizeLumps()
//{
//	TLumpsList founded;
//	TLumpsListIter iter = _tableOfContents.begin();
//	TLumpsListIter iter_end = _tableOfContents.end();
//	while(iter != iter_end)
//	{
//		if ((*iter)->alType() == LUMPTYPES_ZEROSIZE)
//		{
//			founded.push_back(*iter);
//		}
//
//		++iter;
//	}
//
//	return founded;
//}
//
////=============================================================================
//
//void AWAD::amDefineMapLumps(FILE *wadFile)
//{
//	for (TLumpsListIter iter = _tableOfContents.begin(); iter < _tableOfContents.end(); iter++)
//	{
//		if ((*iter)->alSize())
//		{
//			continue;
//		}
//
//		if (checkLumpIfItIsMap(*iter, wadFile) == true)
//		{
//			TLumpsListIter mapLump = awFindLump((*iter)->alName());
////			(*iter) = new AMap(*mapLump);
//		}
//	}
//}
//
////=============================================================================
//
//bool AWAD::checkLumpIfItIsMap(ALump* lump, FILE* wadFile)
//{
//	if (!lump)
//	{
//		return false;
//	}
//
//	std::vector<std::string> mapContentLumpsNames = {"THINGS", "LINEDEFS", "SIDEDEFS", "VERTEXES", "SEGS", "SSECTORS", "NODES", "SECTORS", "REJECT", "BLOCKMAP"};
//	for (std::vector<std::string>::iterator iter = mapContentLumpsNames.begin(); iter < mapContentLumpsNames.end(); iter++)
//	{
//		if (fseek(wadFile, lump->alOffset() + lump->alSize(), SEEK_SET))
//		{
//			return false;
//		}
//		char buffer[256] = {0};
//		int read = fread(buffer, 1, iter->length(), wadFile);
//		std::string bufferString(buffer);
//		if (bufferString.compare(0, iter->length(), *iter) == 0)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
//
////=============================================================================
//
//
////=============================================================================
//
//#pragma mark - Misc -
//
////=============================================================================
//
//bool AWAD::awIntoMidi(const std::string& fileName, ASFX* sfx)
//{
//    if (!sfx)
//        return false;
//
//    FILE* filo = fopen(fileName.c_str(), "wb");
//    if (!filo)
//        return false;
//
//    fwrite(sfx->asData(), sfx->alSize(), 1, filo); //  identity length
//
//    fclose(filo);
//
//    return true;
//}
//
////=============================================================================
//
//bool AWAD::awIntoTga(const std::string& fileName, const AFlat* flat)
//{
//	if (!flat)
//		return false;
//
//    unsigned char* data = const_cast<unsigned char*>(flat->afData());
//    if (!awIntoTga(fileName, data, FLAT_WIDTH, FLAT_HEIGHT))
//        return false;
//
//	return true;
//}
//
////=============================================================================
//
//bool AWAD::awIntoTga(const std::string& fileName, const APatch* patch)
//{
//	if (!patch)
//		return false;
//
//    unsigned char* data = const_cast<unsigned char*>(patch->apData());
//    if (!awIntoTga(fileName, data, patch->apWidth(), patch->apHeight()))
//        return false;
//
//	return true;
//}
//
////=============================================================================
//
//
////=============================================================================
//
//const unsigned int AWAD::awLumpsCount() const
//{
//    return _tableOfContents.size();
//}
//
////=============================================================================
//
};  //  namespace spcWAD
