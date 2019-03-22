#ifndef SPCWAD_AUTILITIES_H
#define SPCWAD_AUTILITIES_H

//=============================================================================

#include <string>

#include "alump.h"
#include "types.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	Some utilities
*/
class AUtilities
{
public:

    /**
     Search of lumps which names begins with lumpsNameMask

     @param lumpsNameMask prefix of lump name to find
     @param lumpsList the list of lumps in which the search should be done
     @return the resulting list of lumps of end iterator in case of no results
     */
    static TLumpsList findLumpsList(const std::string& lumpsNameMask, const TLumpsList& lumpsList);

    /**
     Search of flat in flat lists with exact name flatNameToFind

     @param flatNameToFind name of flat to find
     @param flatList list in which the search should be done
     @return reference to founded flat
     */
    static const AFlat& findFlat(const std::string& flatNameToFind, const TFlatsList& flatList);

    /**
     Search of lump iterator in lumps list

     @param lumpNameToFind exasct name of lump to find
     @param lumpsList list in which the search should be done
     @return const iterator to founded lump
     */
    static TLumpsListConstIter findLumpIter(const std::string& lumpNameToFind, const TLumpsList& lumpsList);

    /**
     Read data of lump lumpToRead from file into already allocated memory lumpData

     @param wadFile file pointer to wad file
     @param lumpToRead lump which should be read
     @param lumpData allocated memory where to read the data
     @return true in case of success, or false in case of error
     */
    static bool readLumpData(FILE* wadFile, const ALump& lumpToRead, unsigned char *lumpData);

    /**
     converts booth strings to lower case and then compares on equality

     @param one first string
     @param two second string
     @return result of comparison
     */
    static bool stringCompare(const std::string& one, const std::string& two);

    /**
     Checks if prefix string is the begining of string

     @param prefix prefix which should be the start of string
     @param string the string in which we are trying to find prefix
     @return result of comparison, true if prefix is the prefix of string and false in other cases
     */
    static bool stringPrefixCompare(const std::string& prefix, const std::string& string);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AUTILITIES_H
