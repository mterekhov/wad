#ifndef SPCWAD_ALUMP_H
#define SPCWAD_ALUMP_H

//=============================================================================

#include <string>

#include "enums.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class is the description of everything in wad file
*/
class ALump
{
public:
	ALump(const int size, const int offset, const std::string& name);
	~ALump();

    int lumpSize;
    int lumpOffset;
    std::string lumpName;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALUMP_H
