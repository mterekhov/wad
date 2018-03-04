#ifndef SPCWAD_APALETE_H
#define SPCWAD_APALETE_H

//=============================================================================

#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class operates with palette for all images in resources
*/
class APalete
{
public:
    APalete(unsigned char* incomingData, const int incomingSize);
    ~APalete();
	APalete& operator=(const APalete& rv);

    const unsigned char red(const int index) const;
    const unsigned char green(const int index) const;
    const unsigned char blue(const int index) const;

private:
	int _paleteSize;
    unsigned char* _paleteData;
	
    void destroy();
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APALETE_H
