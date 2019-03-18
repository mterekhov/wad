#ifndef SPCWAD_TYPES_H
#define SPCWAD_TYPES_H

//=============================================================================

#include <vector>
#include <list>

//=============================================================================

namespace spcWAD
{

//=============================================================================

#define PIXEL_TRANSPARENCY_MARKER 1

//=============================================================================

class ALump;
class ADemo;
class AFlat;
class APicture;
class ATexture;
class AThing;
class ASprite;

//=============================================================================

struct SPatchDescription
{
	int x_offset;
	int y_offset;

	APicture& patch;
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

typedef std::vector<APicture> TIndexedPicturesList;
typedef TIndexedPicturesList::iterator TIndexedPicturesListIter;
typedef TIndexedPicturesList::const_iterator TIndexedPicturesListConstIter;

typedef std::vector<APicture> TPicturesList;
typedef TPicturesList::iterator TPicturesListIter;
typedef TPicturesList::const_iterator TPicturesListConstIter;

typedef std::list<ATexture> TTexturesList;
typedef TTexturesList::iterator TTexturesListIter;

typedef std::list<SPatchDescription> TPatchesDescriptionList;
typedef TPatchesDescriptionList::iterator TPatchesDescriptionListIter;
typedef TPatchesDescriptionList::const_iterator TPatchesDescriptionListConstIter;

typedef std::vector<AThing> TThingList;
typedef TThingList::iterator TThingListIter;
typedef TThingList::const_iterator TThingListConstIter;

typedef std::list<ASprite> TSpriteList;
typedef TSpriteList::iterator TSpriteListIter;
typedef TSpriteList::const_iterator TSpriteListConstIter;

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_TYPES_H

