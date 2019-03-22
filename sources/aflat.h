#ifndef SPCWAD_AFLAT_H
#define SPCWAD_AFLAT_H

//=============================================================================

#include <string>

#include "aimagedata.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

class APalete;

//=============================================================================

/**
	This class is used to describe the texture of floor and ceiling only. It is size is always 64x64 pixel. For walls should be used ATexture class.
*/
class AFlat
{
public:
	AFlat(unsigned char* incomingData, const std::string& incomingName, const APalete& palete);
	AFlat(const AFlat& flat);
    ~AFlat();
	AFlat& operator=(const AFlat& rv);

	bool saveFlatIntoTga(const std::string& fileName);
	const std::string& flatName() const;
    
private:
    std::string _flatName;
    AImageData _imageData;

	void convertData(unsigned char* incomingData, const APalete& palete);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AFLAT_H
