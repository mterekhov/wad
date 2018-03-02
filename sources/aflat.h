#ifndef SPCWAD_AFLAT_H
#define SPCWAD_AFLAT_H

//=============================================================================

#include <string>

//=============================================================================

namespace spcWAD
{

//=============================================================================

class APalete;

//=============================================================================

/**
	This class is the base image
*/
class AFlat
{
public:
	AFlat(unsigned char* incomingData, const int incomingSize, const std::string& incomingName, const APalete& palete);
	AFlat(const AFlat& flat);
    ~AFlat();
	AFlat& operator=(const AFlat& rv);

	bool saveFlatIntoTga(const std::string& fileName);
	std::string flatName() const;
	unsigned char* flatData() const;

private:
	int _flatSize;
    unsigned char* _flatData;
    std::string _flatName;

	int flatHeightSize();
	int flatWidthSize();
	unsigned char* convertData(unsigned char* incomingData, const int incomingSize, int* outgoindSize, const APalete& palete);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AFLAT_H
