#ifndef SPCWAD_AWAD_H
#define SPCWAD_AWAD_H

//=============================================================================

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "types.h"
#include "aflat.h"
#include "apatch.h"
#include "asfx.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

enum EWadType
{
    WADTYPE_UNKNOWN,
    WADTYPE_INTERNAL_WAD,
    WADTYPE_PATCH_WAD
};

//=============================================================================

class WAD_DLL AWAD
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
    FILE* awOpen(const std::string& fileName);
    void awClose(FILE* wadFile);
    void awDestroy();

    //  Get wad file type
    bool awCheckSignature(FILE* wadFile);

    //  read content
    bool awReadLumpsContent(FILE* wadFile);
    //  read palete
    bool awReadPalete(FILE* wadFile);
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

    TSeqIter awFindLump(const std::string& name);

    bool awIntoTga(const std::string& fileName, unsigned char* data, const int width, const int height);
    bool RGB2BGR(unsigned char* data, int width, int height);
    bool FlipOver(unsigned char* data, int width, int height);

    TSequence m_lumps;
    std::map<int, APatch*> m_patchesIndexes;
    EWadType m_type;
    std::string m_fileName;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AWAD_H
