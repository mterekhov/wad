#ifndef SPCWAD_ASFX_H
#define SPCWAD_ASFX_H

//=============================================================================

#include "apalete.h"
#include "types.h"

//=============================================================================

#define FLAT_WIDTH 64
#define FLAT_HEIGHT 64

//=============================================================================

namespace spcWAD
{

//=============================================================================

class WAD_DLL ASFX : public ALump
{
public:
    ASFX(const ALump& lump);
    virtual ~ASFX();

    bool asReadData(APalete& palete, FILE* wadFile);
    const unsigned char* asData() const;

protected:
    void asDestroy();

    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ASFX_H
