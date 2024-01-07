#ifndef SPCWAD_ALEVELINTEGRITY_H
#define SPCWAD_ALEVELINTEGRITY_H

//=============================================================================

#include <string>

//=============================================================================

namespace spcWAD
{
    
//=============================================================================

/**
 Thye main purpose of this class is to check the integrity of level in terms of lumps. Every level must have a critical number of lumps so the engine can render the level. This class check that the level has all the lumps it needs
 */
class ALevelIntegrity
{
private:
    int _completeIntegrity;
    
    int calculateCompleteIntegrity();
    int integrityEnum(const std::string& integrityString);

public:
    ALevelIntegrity();
    ~ALevelIntegrity();
    
    int appendIntegrity(const int currentIntegrity, const std::string& levelLumpName);
    bool checkIntegrity(const int integrityToCheck);
};

//=============================================================================
    
};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALEVELINTEGRITY_H
