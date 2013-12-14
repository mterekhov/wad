#ifndef SPCWAD_ALUMP_H
#define SPCWAD_ALUMP_H

//=============================================================================

#include <string>

#include "types.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

enum ELumpTypes
{
    LUMPTYPES_FLATS,
    LUMPTYPES_TEXTURES,
    LUMPTYPES_PATCHES,
    LUMPTYPES_SFX,
    LUMPTYPES_PCSPEAKER,

    LUMPTYPES_COUNT,
    LUMPTYPES_UNKNOWN,
    LUMPTYPES_PALETE
};

//=============================================================================

class WAD_DLL ALump
{
public:
    ALump(const int size, const int offset, const std::string& name, ELumpTypes type = LUMPTYPES_UNKNOWN);
    virtual ~ALump();

    const ELumpTypes alType() const;
    const int alSize() const;
    const int alOffset() const;
    const std::string& alName() const;
    const bool alUsed() const;

protected:
    bool alReadLump(FILE* wadFile, unsigned char* data);
    void alDestroy(unsigned char* data);

    bool m_used;

private:
    ELumpTypes m_type;
    int m_size;
    int m_offset;
    std::string m_name;
};

//=============================================================================

typedef std::vector<ALump*> TSequence;
typedef std::vector<ALump*>::iterator TSeqIter;

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALUMP_H
