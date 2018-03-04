#include <stdio.h>

#include "awad.h"
#include "alump.h"
#include "apalete.h"
#include "aflat.h"
#include "atexture.h"
#include "afindhelper.h"

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

//    if (!readTextures(wadFile))
//        throw;


	for (TPatchesListIter iter = _patchesList.begin(); iter != _patchesList.end(); iter++)
	{
		APatch& patch = *iter;
		std::string path = "/Users/michael/Pictures/saved/";
		path += patch.patchName();
		printf("<%s>\n", patch.patchName().c_str());
		path += ".tga";
		patch.savePatchIntoTga(path);
	}
//	for (TFlatsListIter iter = _flatsList.begin(); iter != _flatsList.end(); iter++)
//	{
//		AFlat& flat = *iter;
//		std::string path = "/Users/michael/Pictures/saved/";
//		path += flat.flatName();
//		path += ".tga";
//		flat.saveFlatIntoTga(path);
//	}
//	for (TTexturesListIter iter = _texturesList.begin(); iter < _texturesList.end(); iter++)
//	{
//		ATexture& texture = *iter;
//		std::string path = "/Users/michael/Pictures/saved/";
//		path += texture.textureName();
//		path += ".tga";
//		texture.saveTextureIntoTga(path);
//	}

//	int counter = 1;
//	for (TLumpsListIter iter = _tableOfContents.begin(); iter < _tableOfContents.end(); iter++)
//	{
//		printf("%i. %s\t%x\n", counter++, (*iter).lumpName.c_str(), (*iter).lumpOffset);
//	}
//
//	counter = 1;
//	for (TPatchesListIter iter = _patchesList.begin(); iter < _patchesList.end(); iter++)
//	{
//		printf("%i. %s\n", counter++, (*iter).patchName.c_str());
//	}

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
	const ALump& playpalLump = AFindHelper::findLump("PLAYPAL", _tableOfContents);

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
	const ALump& colorMapLump = AFindHelper::findLump("COLORMAP", _tableOfContents);

	unsigned char *lumpData = new unsigned char [colorMapLump.lumpSize];
    memset(lumpData, 0, colorMapLump.lumpSize);
	
	readLumpData(wadFile, colorMapLump, lumpData);

	_colorMap = AColorMap(lumpData, colorMapLump.lumpSize);

	delete [] lumpData;

	return true;
}

//=============================================================================

bool AWAD::readEndDoom(FILE* wadFile)
{
	const ALump& endoomLump = AFindHelper::findLump("ENDOOM", _tableOfContents);

	unsigned char *lumpData = new unsigned char [endoomLump.lumpSize];
    memset(lumpData, 0, endoomLump.lumpSize);
	
	readLumpData(wadFile, endoomLump, lumpData);

	_enDoom = AEnDoom(lumpData, endoomLump.lumpSize);

	delete [] lumpData;

	return true;
}

//=============================================================================

bool AWAD::readDemos(FILE* wadFile)
{
	TLumpsList demosList = findLumpsList("DEMO");
	for (TLumpsListIter iter = demosList.begin(); iter != demosList.end(); iter++)
	{
		const ALump& demoLump = AFindHelper::findLump(iter->lumpName, _tableOfContents);
		unsigned char *lumpData = new unsigned char [demoLump.lumpSize];
		memset(lumpData, 0, demoLump.lumpSize);
		
		readLumpData(wadFile, demoLump, lumpData);

		ADemo newDemo(lumpData, demoLump.lumpSize, demoLump.lumpName);
		_demosList.push_back(newDemo);
		
		delete [] lumpData;
	}

	return true;
}

//=============================================================================

bool AWAD::readFlats(FILE* wadFile)
{
//    //  read first part of flats
//    if (!readFlatsRange(wadFile, "F1_START", "F1_END"))
//        return false;

    //  read second part of flats
    if (!readFlatsRange(wadFile, "F_START", "F_END"))
        return false;

    return true;
}

//=============================================================================

bool AWAD::readFlatsRange(FILE* wadFile, const std::string& beginLumpName, const std::string& endLumpName)
{
	TLumpsListConstIter beginLump = AFindHelper::findLumpIter(beginLumpName, _tableOfContents);
	TLumpsListConstIter endLump = AFindHelper::findLumpIter(endLumpName, _tableOfContents);
    TLumpsListIter lumpListEnd = _tableOfContents.end();
	
    if ((beginLump != lumpListEnd) && (endLump != lumpListEnd))
    {
        ++beginLump;
		for (TLumpsListConstIter iter = beginLump; iter != endLump; iter++)
		{
			ALump flatLump = (*iter);
			unsigned char *lumpData = new unsigned char [flatLump.lumpSize];
			memset(lumpData, 0, flatLump.lumpSize);
			
			readLumpData(wadFile, flatLump, lumpData);
			
			AFlat newFlat(lumpData, flatLump.lumpName, _palete);
			_flatsList.push_back(newFlat);
			
			delete [] lumpData;
		}
    }

    return true;
}

//=============================================================================

bool AWAD::readPatches(FILE* wadFile)
{
	const ALump& pNamesLump = AFindHelper::findLump("PNAMES", _tableOfContents);
    fseek(wadFile, pNamesLump.lumpOffset, SEEK_SET);
    int patchesCount = 0;
    if (fread(&patchesCount, 4, 1, wadFile) != 1)
    {
        return false;
	}

	unsigned char *patchData = 0;
    for (int i = 0; i < patchesCount; i++)
    {
        char patchLumpName[9] = {0};
        if (fread(patchLumpName, 8, 1, wadFile) != 1)
        {
            return false;
		}

		const ALump& patchLump = AFindHelper::findLump(patchLumpName, _tableOfContents);
		patchData = new unsigned char[patchLump.lumpSize];
		memset(patchData, 0, patchLump.lumpSize);
		long patchesPosition = ftell(wadFile);
		readLumpData(wadFile, patchLump, patchData);
		fseek(wadFile, patchesPosition, SEEK_SET);

		APatch newPatch(patchData, patchLumpName, _palete);
		_patchesList.push_back(newPatch);

		delete [] patchData;
		patchData = 0;
    }

    return true;
}

//=============================================================================

bool AWAD::readTextures(FILE* wadFile)
{
	const ALump& textureLump = AFindHelper::findLump("TEXTURE1", _tableOfContents);
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

	for (std::vector<int>::iterator iter = texturesOffsetsList.begin(); iter < texturesOffsetsList.end(); iter++)
	{
		_texturesList.push_back(generateSingleTexture(wadFile, (*iter)));
		break;
	}
	
    return true;
}

//=============================================================================

ATexture AWAD::generateSingleTexture(FILE* wadFile, const int textureOffset)
{
	fseek(wadFile, textureOffset, SEEK_SET);
	char textureName[9] = {0};
	fread(textureName, 8, 1, wadFile);
	int buffer = 0;
	fread(&buffer, 4, 1, wadFile);
	int width = 0;
	fread(&width, 2, 1, wadFile);
	int height = 0;
	fread(&height, 2, 1, wadFile);
	fread(&buffer, 4, 1, wadFile);
	int patchNumbers = 0;
	fread(&patchNumbers, 2, 1, wadFile);
	printf("<%s> size %ix%i patch numbers %i\n", textureName, width, height, patchNumbers);

	TPatchesDescriptionList patchesDescriptionList;
	for (int patchIndex = 0; patchIndex < patchNumbers; patchIndex++)
	{
		int xOffset = 0;
		fread(&xOffset, 2, 1, wadFile);
		int yOffset = 0;
		fread(&yOffset, 2, 1, wadFile);
		int patchIndexInPatchDirectory = 0;
		fread(&patchIndexInPatchDirectory, 2, 1, wadFile);
		fread(&buffer, 4, 1, wadFile);

		APatch& patch = AFindHelper::findPatch(patchIndexInPatchDirectory, _patchesList);
		SPatchDescription newDescription = {xOffset, yOffset, patch};
		patchesDescriptionList.push_back(newDescription);
		printf("\t\t\tx_offset = %i, y_offset = %i, patchIndex = %i\n", xOffset, yOffset, patchIndexInPatchDirectory);
	}
	
	ATexture newTexture(patchesDescriptionList, textureName, width, height);
	return newTexture;
}

//=============================================================================

#pragma mark - Lump operations -

//=============================================================================

bool AWAD::readLumpData(FILE* wadFile, const ALump& lumpToRead, unsigned char *lumpData)
{
	if (fseek(wadFile, lumpToRead.lumpOffset, SEEK_SET))
	{
		return false;
	}
	
	int read = fread(lumpData, lumpToRead.lumpSize, 1, wadFile);
	if (read != 1)
	{
		return false;
	}
	
	return true;
}

//=============================================================================

TLumpsList AWAD::findLumpsList(const std::string& lumpsNameMask)
{
	TLumpsList founded;
	for (TLumpsListIter iter = _tableOfContents.begin(); iter != _tableOfContents.end(); iter++)
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
