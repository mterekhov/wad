#ifndef SPCWAD_ATEXTURE_H
#define SPCWAD_ATEXTURE_H

//=============================================================================

#include "apatch.h"

#include <map>

//=============================================================================

namespace spcWAD
{

//=============================================================================

class WAD_DLL ATexture : public ALump
{
public:
    ATexture(const ALump& lump);
    virtual ~ATexture();

    bool atReadData(const std::map<int, APatch*>& patches, FILE* wadFile);
    const unsigned char* atData() const;
    const int atWidth() const;
    const int atHeight() const;

protected:
    void atDestroy();

    int m_width;
    int m_height;
    unsigned char* m_pData;
    std::vector<APatch*> m_patches;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ATEXTURE_H
