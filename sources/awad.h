#ifndef SPCWAD_AWAD_H
#define SPCWAD_AWAD_H

//=============================================================================

#include <stdio.h>
#include <string>
#include <map>

#include "types.h"
#include "enums.h"

//=============================================================================

namespace spcWAD
{

class AFlat;
class APatch;
class ASFX;

//=============================================================================

class AWAD
{
public:
    AWAD(const std::string& fileName);
    ~AWAD();

    const TSequence& awLumps() const;
    TSequence& awLumps();
    
    TSequence awFilteredLumps(const ELumpTypes type);

    const ALump* awGetLump(const std::string& name);
    const unsigned int awLumpsCount() const;
    const std::string& awFileName() const;
    bool awIntoTga(const std::string& fileName, const AFlat* flat);
    bool awIntoTga(const std::string& fileName, const APatch* patch);
    bool awIntoMidi(const std::string& fileName, ASFX* sfx);

private:
    EWadType _type;
    std::string _fileName;
    TSequence _tableOfContents;

    void destroy();
    bool checkSignature(FILE* wadFile);
	bool readTableOfContents(FILE* wadFile);
//=========================================
    std::map<int, APatch*> _patchesIndexes;

	
	bool checkLumpIfItIsMap(ALump* lump, FILE* wadFile);
	
	//  read palete
	bool awReadPalete(FILE* wadFile);
	//	read colors map
	bool awReadColorMap(FILE* wadFile);
	//	read endoom texts
	bool awReadEndDoom(FILE* wadFile);
	//	read demos
	bool awReadDemos(FILE* wadFile);
	//  read flats
    bool awReadFlats(FILE* wadFile);
    bool awReadFlatRange(FILE* wadFile, TSeqIter iter, TSeqIter iter_end);
    //  read patches
    bool awReadPatches(FILE* wadFile);
    //  read textures
    bool awReadTextures(FILE* wadFile);
    //  read digital sounds
    bool awReadSFX(FILE* wadFile);
    //  read ps speaker sounds
	bool awReadPCSpeaker(FILE* wadFile);
	
	bool awReadMaps(FILE* wadFile);

	void amDefineMapLumps(FILE *wadFile);
	TSequence awFindZeroSizeLumps();
	TSequence awFindLumpsList(const std::string& lumpsNameMask);
    TSeqIter awFindLump(const std::string& name);

    bool awIntoTga(const std::string& fileName, unsigned char* data, const int width, const int height);
    bool RGB2BGR(unsigned char* data, int width, int height);
    bool FlipOver(unsigned char* data, int width, int height);

};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AWAD_H
