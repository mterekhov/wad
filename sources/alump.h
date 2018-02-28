#ifndef SPCWAD_ALUMP_H
#define SPCWAD_ALUMP_H

//=============================================================================

#include <string>

#include "enums.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================


//=============================================================================

class ALump
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

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALUMP_H
