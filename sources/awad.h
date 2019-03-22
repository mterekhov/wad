#ifndef SPCWAD_AWAD_H
#define SPCWAD_AWAD_H

//=============================================================================

#include <stdio.h>
#include <string>
#include <map>

#include "types.h"
#include "enums.h"
#include "apalete.h"
#include "acolormap.h"
#include "aendoom.h"
#include "ademo.h"
#include "apicture.h"
#include "atexture.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

class ALevel;
    
//=============================================================================

/**
	This class reads all the content from the wad file format
*/
class AWAD
{
public:
    AWAD(const std::string& fileName);
    ~AWAD();
    ALevel readLevel(const std::string& levelName);

private:
	APalete _palete;    //  palete for every image resource
	AColorMap _colorMap;    //  map of colors for different light areas
	AEnDoom _enDoom;    //  texts which are shown when the game finished
    TDemosList _demosList;  //  list of demos which are playing at games start
	TFlatsList _flatsList;  //  textures for floor and ceiling

	TIndexedPicturesList _patchesList;  //  list of patches out of which wall textures are created
	TTexturesList _texturesList;    //  list of textures for walls
    EWadType _type; //  type of wad file - IWAD or PWAD
    std::string _fileName;  //  name of wad file which was parsed
    TLumpsList _tableOfContents;    //  list of all lumps in wad file

    bool checkSignature(FILE* wadFile);
	bool readTableOfContents(FILE* wadFile);
	bool readPalete(FILE* wadFile);
	bool readColorMap(FILE* wadFile);
	bool readEndDoom(FILE* wadFile);
	bool readDemos(FILE* wadFile);
	bool readFlats(FILE* wadFile);
	bool readFlatsRange(FILE* wadFile, const std::string& beginLumpName, const std::string& endLumpName);
	bool readPatches(FILE* wadFile);
	bool readTextures(FILE* wadFile);
	ATexture generateSingleTexture(const int textureOffset, unsigned char *lumpData);
	
	bool readLevel(FILE* wadFile);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AWAD_H
