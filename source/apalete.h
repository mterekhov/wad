#ifndef SPCWAD_APALETE_H
#define SPCWAD_APALETE_H

//=============================================================================

#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

#define PALETE_NUMBER 42

//=============================================================================

class WAD_DLL APalete : public ALump
{
public:
    APalete(const ALump& lump);
    virtual ~APalete();

    bool apReadData(FILE* wadFile);
    const unsigned char apRed(const int index) const;
    const unsigned char apGreen(const int index) const;
    const unsigned char apBlue(const int index) const;

protected:
    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APALETE_H
