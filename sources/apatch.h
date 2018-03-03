#ifndef SPCWAD_APATCH_H
#define SPCWAD_APATCH_H

//=============================================================================

#include <string>

#include "alump.h"
#include "apalete.h"

//=============================================================================

class ALump;

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class is the name and the index of part of a texture
*/
class APatch
{
public:
	APatch(unsigned char* incomingData, const int incomingWidth, const int incomingHeight, const std::string& incomingName, const APalete& palete);
	APatch(const APatch& patch);
    ~APatch();
	APatch& operator=(const APatch& rv);

	int patchDataSize() const;

private:

    unsigned char* _patchData;
	int _patchWidth;
	int _patchHeight;
    std::string _patchName;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APATCH_H
