#ifndef SPCWAD_AMAP_H
#define SPCWAD_AMAP_H

//=============================================================================

#include "apalete.h"


//=============================================================================

namespace spcWAD
{

//=============================================================================

class AThings : public ALump
{
public:
    AThings(const ALump& lump);
    virtual ~AThings();

    bool atReadData(FILE* wadFile);
    const unsigned char* atData() const;

private:

    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AMAP_H
