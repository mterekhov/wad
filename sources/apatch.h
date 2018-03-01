#ifndef SPCWAD_APATCH_H
#define SPCWAD_APATCH_H

//=============================================================================

#include "aflat.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

class APatch
{
public:
	APatch(const AFlat& flat, const int width, const int height, const int x_offset, const int y_offset);
	APatch(const APatch& patch);
    ~APatch();
	APatch& operator=(const APatch& rv);

private:
	int _patchSize;
    unsigned char* _patchData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APATCH_H
