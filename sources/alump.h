#ifndef SPCWAD_ALUMP_H
#define SPCWAD_ALUMP_H

//=============================================================================

#include <string>

#include "enums.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

class ALump
{
public:
	ALump(const int size, const int offset, const std::string& name, ELumpTypes type = LUMPTYPES_UNKNOWN);
	~ALump();

    ELumpTypes lumpType;
    int lumpSize;
    int lumpOffset;
    std::string lumpName;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALUMP_H
