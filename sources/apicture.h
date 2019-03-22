#ifndef SPCWAD_APATCH_H
#define SPCWAD_APATCH_H

//=============================================================================

#include <string>

#include "alump.h"
#include "apalete.h"
#include "aimagedata.h"

//=============================================================================

class ALump;

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class is for main picture format of DOOM, which is used in sprites and textures
*/
class APicture
{
public:
    APicture();
	APicture(const unsigned char* incomingData, const std::string& incomingName, const APalete& palete);
	APicture(const APicture& patch);
    ~APicture();
	APicture& operator=(const APicture& rv);

	const std::string& patchName() const;
	bool savePatchIntoTga(const std::string& fileName);
    AImageData imageData;

private:
	void convertData(const unsigned char* incomingData, const APalete& palete, const int bytesOffset);

    std::string _patchName;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APATCH_H
