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
	
    if (!readFlats(wadFile))
        throw;

    if (!readPatches(wadFile))
        throw;

    if (!readTextures(wadFile))
        throw;
	if (!readColorMap(wadFile))
		throw;

	if (!readEndDoom(wadFile))
		throw;

	if (!readDemos(wadFile))
		throw;

//	for (TPatchesListIter iter = _patchesList.begin(); iter != _patchesList.end(); iter++)
//	{
//		APatch& patch = *iter;
//		std::string path = "/Users/michael/Pictures/saved/";
//		path += patch.patchName();
//		printf("<%s>\n", patch.patchName().c_str());
//		path += ".tga";
//		patch.savePatchIntoTga(path);
//	}
//	
//	for (TFlatsListIter iter = _flatsList.begin(); iter != _flatsList.end(); iter++)
//	{
//		AFlat& flat = *iter;
//		std::string path = "/Users/michael/Pictures/saved/";
//		path += flat.flatName();
//		path += ".tga";
//		flat.saveFlatIntoTga(path);
//	}
	int i = 0;
	for (TLumpsListIter iter = _tableOfContents.begin(); iter != _tableOfContents.end(); iter++)
	{
		printf("%i. <%s>\n", ++i, iter->lumpName.c_str());
	}

	for (TTexturesListIter iter = _texturesList.begin(); iter != _texturesList.end(); iter++)
	{
		ATexture& texture = *iter;
		std::string path = "/Users/michael/Pictures/saved/";
		path += texture.textureName();
		path += ".tga";
		texture.saveTextureIntoTga(path);
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
	const ALump& playpalLump = AFindHelper::findLump("PLAYPAL", _tableOfContents);

	unsigned char *lumpData = new unsigned char [playpalLump.lumpSize];
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
    if (!readFlatsRange(wadFile, "F1_START", "F1_END"))
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
	TLumpsListConstIter pNamesLumpIter = AFindHelper::findLumpIter("PNAMES", _tableOfContents);
	if (pNamesLumpIter == _tableOfContents.end())
	{
		return false;
	}
	
	const ALump& patchesNamesLump = *pNamesLumpIter;
	unsigned char *lumpData = new unsigned char [patchesNamesLump.lumpSize];
	readLumpData(wadFile, patchesNamesLump, lumpData);
	int bytesOffset = 0;

    int patchesCount = 0;
    memcpy(&patchesCount, lumpData, 4);
    bytesOffset += 4;

	//	Read all patches lumps names
	std::list<std::string> patchesLumpsNamesList;
	int patchNameSizeInBytes = 8;
	for (int i = 0; i < patchesCount; i++)
	{
		char patchName[9] = {0};
	    memcpy(patchName, &lumpData[bytesOffset], patchNameSizeInBytes);
	    bytesOffset += patchNameSizeInBytes;
		patchesLumpsNamesList.push_back(patchName);
	}
	delete [] lumpData;

	//	Read all PATCHES pointed in list
	for (std::list<std::string>::iterator iter = patchesLumpsNamesList.begin(); iter != patchesLumpsNamesList.end(); iter++)
	{
		std::string patchLumpName = *iter;
		TLumpsListConstIter patchLumpIter = AFindHelper::findLumpIter(patchLumpName, _tableOfContents);
		if (patchLumpIter == _tableOfContents.end())
		{
			printf("NO CHANCE TO FIND <%s>\n", patchLumpName.c_str());
			continue;
		}
		const ALump& patchLump = *patchLumpIter;
		if (!patchLump.lumpSize)
		{
			continue;
		}
		lumpData = new unsigned char [patchLump.lumpSize];
		readLumpData(wadFile, patchLump, lumpData);

		APatch newPatch(lumpData, patchLumpName, _palete);
		_patchesList.push_back(newPatch);

		delete [] lumpData;
	}

    return true;
}

//=============================================================================

bool AWAD::readTextures(FILE* wadFile)
{
	TLumpsListConstIter textureLumpIter = AFindHelper::findLumpIter("TEXTURE2", _tableOfContents);
	if (textureLumpIter == _tableOfContents.end())
	{
		return false;
	}
	
	const ALump& textureLump = *textureLumpIter;
	unsigned char *lumpData = new unsigned char [textureLump.lumpSize];
	readLumpData(wadFile, textureLump, lumpData);
	int bytesOffset = 0;

    int texturesCount = 0;
    memcpy(&texturesCount, lumpData, 4);
	bytesOffset += 4;

	std::vector<int> texturesOffsetsList;
    for (int i = 0; i < texturesCount; i++)
    {
	    int textureOffset = 0;
		memcpy(&textureOffset, &lumpData[bytesOffset], 4);
		bytesOffset += 4;

		texturesOffsetsList.push_back(textureOffset);
    }

	for (std::vector<int>::iterator iter = texturesOffsetsList.begin(); iter != texturesOffsetsList.end(); iter++)
	{
		_texturesList.push_back(generateSingleTexture((*iter), lumpData));
	}
	
	delete [] lumpData;
	
    return true;
}

//=============================================================================

ATexture AWAD::generateSingleTexture(const int textureOffset, unsigned char *lumpData)
{
	int bytesOffset = textureOffset;
	char textureName[9] = {0};
	memcpy(textureName, &lumpData[bytesOffset], 8);
	bytesOffset += 8;
	bytesOffset += 4;	//	skiping 4 bytes
	short textureWidth = 0;
	memcpy(&textureWidth, &lumpData[bytesOffset], 2);
	bytesOffset += 2;
	short textureHeight = 0;
	memcpy(&textureHeight, &lumpData[bytesOffset], 2);
	bytesOffset += 2;
	bytesOffset += 4;	//	skiping 4 bytes
	short texturePatchNumbers = 0;
	memcpy(&texturePatchNumbers, &lumpData[bytesOffset], 2);
	bytesOffset += 2;

	TPatchesDescriptionList patchesDescriptionList;
	for (int patchIndex = 0; patchIndex < texturePatchNumbers; patchIndex++)
	{
		short xOffset = 0;
		memcpy(&xOffset, &lumpData[bytesOffset], 2);
		bytesOffset += 2;

		short yOffset = 0;
		memcpy(&yOffset, &lumpData[bytesOffset], 2);
		bytesOffset += 2;
		
		int patchIndexInPatchDirectory = 0;
		memcpy(&patchIndexInPatchDirectory, &lumpData[bytesOffset], 2);
		bytesOffset += 2;
		bytesOffset += 4;	//	skiping 4 bytes

		if ((patchIndexInPatchDirectory > _patchesList.size()) || (patchIndexInPatchDirectory < 0))
		{
			printf("\t\t\t%s can not be created because patch does not exist\n", textureName);
			continue;
		}

		SPatchDescription newDescription = {xOffset, yOffset, _patchesList[patchIndexInPatchDirectory]};
		patchesDescriptionList.push_back(newDescription);
	}
	
	ATexture newTexture(patchesDescriptionList, textureName, textureWidth, textureHeight);
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
	
	memset(lumpData, 0, lumpToRead.lumpSize);
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
	std::string findLump;
	findLump.resize(lumpsNameMask.size());
	std::transform(lumpsNameMask.begin(),
				   lumpsNameMask.end(),
				   findLump.begin(),
				   ::tolower);

	TLumpsList founded;
	for (TLumpsListIter iter = _tableOfContents.begin(); iter != _tableOfContents.end(); iter++)
	{
		std::string lumpName;
		lumpName.resize(iter->lumpName.size());
		std::transform(iter->lumpName.begin(),
					   iter->lumpName.end(),
					   iter->lumpName.begin(),
					   ::tolower);
		if (lumpName.compare(0, findLump.length(), findLump) == 0)
		{
			founded.push_back(*iter);
		}
	}

	return founded;
}

//=============================================================================

};  //  namespace spcWAD
