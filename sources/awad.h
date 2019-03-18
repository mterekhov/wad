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

/**
	This class reads all the content from the wad file format
*/
class AWAD
{
public:
    AWAD(const std::string& fileName);
    ~AWAD();

private:
	APalete _palete;
	AColorMap _colorMap;
	AEnDoom _enDoom;
	TDemosList _demosList;
	TFlatsList _flatsList;
	TIndexedPicturesList _patchesList;
	TTexturesList _texturesList;

    EWadType _type;
    std::string _fileName;
    TLumpsList _tableOfContents;

    void destroy();
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
