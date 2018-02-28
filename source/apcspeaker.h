#ifndef SPCWAD_APCSPEAKER_H
#define SPCWAD_APCSPEAKER_H

//=============================================================================

#include "apalete.h"


//=============================================================================

namespace spcWAD
{

//=============================================================================

class APCSpeaker : public ALump
{
public:
    APCSpeaker(const ALump& lump);
    virtual ~APCSpeaker();

    bool apReadData(FILE* wadFile);
    const unsigned char* apData() const;

protected:
    void apDestroy();

    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APCSPEAKER_H
