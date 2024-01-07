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
	This class is the description of lump in wad file. This class doesn't store any data, it describes where in wad file the data stores, what is the size of data and by what name it is in use.
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
