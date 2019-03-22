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
    
    const unsigned char* patchData() const;
    int patchDataSize() const;
    int patchHeightSize() const;
    int patchWidthSize() const;
	bool savePatchIntoTga(const std::string& fileName);

private:
	void destroy();
	unsigned char* convertData(const unsigned char* incomingData, const APalete& palete, const int bytesOffset);

    std::string _patchName;

    unsigned char* _patchData;
    short _patchWidth;
    short _patchHeight;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APATCH_H
