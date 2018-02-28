#ifndef SPCWAD_APATCH_H
#define SPCWAD_APATCH_H

//=============================================================================


#include "apalete.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

class APatch : public ALump
{
public:
    APatch(const ALump& lump);
    virtual ~APatch();

    bool apReadData(const ALump& lump, APalete& palete, FILE* wadFile);
    const unsigned char* apData() const;
    const int apWidth() const;
    const int apHeight() const;

protected:
    int m_width;
    int m_height;
    int m_xoffset;
    int m_yoffset;
    unsigned char* m_pData;

    void apDestroy();
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APATCH_H
