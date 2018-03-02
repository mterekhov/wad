#ifndef SPCWAD_APATCH_H
#define SPCWAD_APATCH_H

//=============================================================================

#include <string>

//=============================================================================

namespace spcWAD
{

//=============================================================================

class APatch
{
public:
	APatch(const std::string& name, const int index);
    ~APatch();

private:
	std::string _patchName;
	int _patchIndex;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APATCH_H
