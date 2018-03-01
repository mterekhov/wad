#ifndef SPCWAD_AWAD_H
#define SPCWAD_AWAD_H

//=============================================================================

#include <stdio.h>
#include <string>
#include <map>

#include "types.h"
#include "enums.h"
#include "apalete.h"
#include "acolormap.h"
#include "aendoom.h"
#include "ademo.h"
#include "apatch.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

class AWAD
{
public:
    AWAD(const std::string& fileName);
    ~AWAD();

private:
	APalete _palete;
	AColorMap _colorMap;
	AEnDoom _enDoom;
	TDemosList _demosList;
	TFlatsList _flatsList;
	TPatchesList _patchesList;

    EWadType _type;
    std::string _fileName;
    TLumpsList _tableOfContents;

    void destroy();
    bool checkSignature(FILE* wadFile);
	bool readTableOfContents(FILE* wadFile);
	bool readPalete(FILE* wadFile);
	bool readColorMap(FILE* wadFile);
	bool readEndDoom(FILE* wadFile);
	bool readDemos(FILE* wadFile);

	bool readFlats(FILE* wadFile);
	bool readFlatsRange(FILE* wadFile, const std::string& beginLumpName, const std::string& endLumpName);

	bool readPatches(FILE* wadFile);

	void readLumpData(FILE* wadFile, ALump lumpToRead, unsigned char *lumpData);
	ALump findLump(const std::string& lumpNameToFind);
	TLumpsListIter findLumpIter(const std::string& lumpNameToFind);
	TLumpsList findLumpsList(const std::string& lumpsNameMask);
	AFlat findFlat(const std::string& flatNameToFind);
//=========================================
//    std::map<int, APatch*> _patchesIndexes;
//
//
//	bool checkLumpIfItIsMap(ALump* lump, FILE* wadFile);
//
//	//  read flats
//    bool awReadFlats(FILE* wadFile);
//    bool awReadFlatRange(FILE* wadFile, TLumpsListIter iter, TLumpsListIter iter_end);
//    //  read patches
//    bool awReadPatches(FILE* wadFile);
//    //  read textures
//    bool awReadTextures(FILE* wadFile);
//    //  read digital sounds
//    bool awReadSFX(FILE* wadFile);
//    //  read ps speaker sounds
//	bool awReadPCSpeaker(FILE* wadFile);
//
//	bool awReadMaps(FILE* wadFile);
//
//	void amDefineMapLumps(FILE *wadFile);
//	TLumpsList awFindZeroSizeLumps();
//	TLumpsList awFindLumpsList(const std::string& lumpsNameMask);
//    TLumpsListIter awFindLump(const std::string& name);
//
//    bool awIntoTga(const std::string& fileName, unsigned char* data, const int width, const int height);
//    bool RGB2BGR(unsigned char* data, int width, int height);
//    bool FlipOver(unsigned char* data, int width, int height);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AWAD_H
