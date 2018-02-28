#ifndef SPCWAD_AENDOOM_H
#define SPCWAD_AENDOOM_H

//=============================================================================

#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
 This class operates with colored texts which you can see in console when quit the game
 */
class AEnDoom : public ALump
{
public:
    AEnDoom(const ALump& lump);
    virtual ~AEnDoom();

    bool aeReadData(FILE* wadFile);

protected:
    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AENDOOM_H
