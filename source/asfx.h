#ifndef SPCWAD_ASFX_H
#define SPCWAD_ASFX_H

//=============================================================================

#include "apalete.h"


//=============================================================================

namespace spcWAD
{

//=============================================================================

class ASFX : public ALump
{
public:
    ASFX(const ALump& lump);
    virtual ~ASFX();

    bool asReadData(FILE* wadFile);
    const unsigned char* asData() const;

protected:
    void asDestroy();

    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ASFX_H
