#ifndef SPCWAD_AMAP_H
#define SPCWAD_AMAP_H

//=============================================================================

#include "apalete.h"


//=============================================================================

namespace spcWAD
{

//=============================================================================

class AMap : public ALump
{
public:
	static TSequence amFindMapLumps(FILE* wadFile);
    AMap(const ALump& lump);
    virtual ~AMap();

    bool amReadData(FILE* wadFile);
    const unsigned char* amData() const;

private:
    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AMAP_H
