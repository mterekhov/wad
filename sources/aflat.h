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
	AFlat(unsigned char* incomingData, const std::string& incomingName, const APalete& palete);
	AFlat(const AFlat& flat);
    ~AFlat();
	AFlat& operator=(const AFlat& rv);

	bool saveFlatIntoTga(const std::string& fileName);
	const std::string& flatName() const;
	const unsigned char* flatData() const;
	int flatHeightSize() const;
	int flatWidthSize() const;
	int flatDataSize() const;

private:
    unsigned char* _flatData;
    std::string _flatName;

	void destroy();
	unsigned char* convertData(unsigned char* incomingData, const APalete& palete);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AFLAT_H
