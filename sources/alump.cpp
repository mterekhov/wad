#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ALump::ALump(const int size, const int offset, const std::string& name, ELumpTypes type) : lumpSize(size), lumpOffset(offset), lumpName(name), lumpType(type)
{
	if (size == 0)
	{
		lumpType = LUMPTYPES_ZEROSIZE;
	}
}

//=============================================================================

ALump::~ALump()
{
}

//=============================================================================

};  //  namespace spcWAD
