#ifndef SPCWAD_APATCH_H
#define SPCWAD_APATCH_H

//=============================================================================

#include <string>

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
	APatch(const std::string& name, const int index);
    ~APatch();

	std::string patchName;

private:
	int _patchIndex;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APATCH_H
