#ifndef SPCWAD_ENUMS_H
#define SPCWAD_ENUMS_H

//=============================================================================

namespace spcWAD
{

//=============================================================================

enum EWadType
{
    WADTYPE_UNKNOWN,        //  unknown wad file format
    WADTYPE_INTERNAL_WAD,   //  internal wad file with magic number 'IWAD' which means that it is the original wad file created by idSoftware and stores all the critical data for game lunch
    WADTYPE_PATCH_WAD       //  patch wad file with magic number 'PWAD' which means that this file overrides some resources from IWAD file, and in case of big need you can fill it with all the critical data to replace IWAD file
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ENUMS_H


