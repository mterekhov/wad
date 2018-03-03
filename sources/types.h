#ifndef SPCWAD_TYPES_H
#define SPCWAD_TYPES_H

//=============================================================================

#include <vector>

//=============================================================================

namespace spcWAD
{

//=============================================================================

class ALump;
class ADemo;
class AFlat;
class APatch;
class ATexture;

//=============================================================================

struct SPatchDescription
{
	int x_offset;
	int y_offset;
	int index;
};

//=============================================================================

typedef std::vector<ALump> TLumpsList;
typedef TLumpsList::iterator TLumpsListIter;
typedef TLumpsList::const_iterator TLumpsListConstIter;
typedef std::vector<ADemo> TDemosList;
typedef TDemosList::iterator TDemosListIter;
typedef std::vector<AFlat> TFlatsList;
typedef TFlatsList::iterator TFlatsListIter;
typedef TFlatsList::const_iterator TFlatsListConstIter;
typedef std::vector<APatch> TPatchesList;
typedef TPatchesList::iterator TPatchesListIter;
typedef std::vector<ATexture> TTexturesList;
typedef TTexturesList::iterator TTexturesListIter;

typedef std::vector<SPatchDescription> TPatchesDescriptionList;
typedef TPatchesDescriptionList::iterator TPatchesDescriptionListIter;
typedef TPatchesDescriptionList::const_iterator TPatchesDescriptionListConstIter;

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_TYPES_H

