#ifndef SPCWAD_TYPES_H
#define SPCWAD_TYPES_H

//=============================================================================

#include <vector>
#include <list>

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

	APatch& patch;
};

//=============================================================================

typedef std::list<ALump> TLumpsList;
typedef TLumpsList::iterator TLumpsListIter;
typedef TLumpsList::const_iterator TLumpsListConstIter;

typedef std::list<ADemo> TDemosList;
typedef TDemosList::iterator TDemosListIter;

typedef std::list<AFlat> TFlatsList;
typedef TFlatsList::iterator TFlatsListIter;
typedef TFlatsList::const_iterator TFlatsListConstIter;

typedef std::list<APatch> TPatchesList;
typedef TPatchesList::iterator TPatchesListIter;
typedef TPatchesList::const_iterator TPatchesListConstIter;

typedef std::list<ATexture> TTexturesList;
typedef TTexturesList::iterator TTexturesListIter;

typedef std::list<SPatchDescription> TPatchesDescriptionList;
typedef TPatchesDescriptionList::iterator TPatchesDescriptionListIter;
typedef TPatchesDescriptionList::const_iterator TPatchesDescriptionListConstIter;

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_TYPES_H

