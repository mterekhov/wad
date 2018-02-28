#ifndef SPCWAD_AFLAT_H
#define SPCWAD_AFLAT_H

//=============================================================================

#include "apalete.h"


//=============================================================================

#define FLAT_WIDTH 64
#define FLAT_HEIGHT 64

//=============================================================================

namespace spcWAD
{

//=============================================================================

class AFlat : public ALump
{
public:
    AFlat(const ALump& lump);
    virtual ~AFlat();

    bool afReadData(APalete& palete, FILE* wadFile);
    const unsigned char* afData() const;

protected:
    void afDestroy();

    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AFLAT_H
