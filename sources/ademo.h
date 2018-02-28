#ifndef SPCWAD_ADEMO_H
#define SPCWAD_ADEMO_H

//=============================================================================

#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class operates with data for demos at the begining of the game
*/
class ADemo : public ALump
{
public:
    ADemo(const ALump& lump);
    virtual ~ADemo();

    bool adReadData(FILE* wadFile);

protected:
    unsigned char* m_pData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ADEMO_H
