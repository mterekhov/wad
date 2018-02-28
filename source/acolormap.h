#ifndef SPCWAD_ACOLORMAP_H
#define SPCWAD_ACOLORMAP_H

//=============================================================================

#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class operates with colors maps which are used to color the entire screen. For example when you are wearing radiation suit it's all become in green
*/
class AColorMap : public ALump
{
public:
    AColorMap(const ALump& lump);
    virtual ~AColorMap();

    bool acReadData(FILE* wadFile);

protected:
    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ACOLORMAP_H
