#ifndef SPCWAD_ALEVELINTEGRITY_H
#define SPCWAD_ALEVELINTEGRITY_H

//=============================================================================

#include <string>

//=============================================================================

namespace spcWAD
{
    
//=============================================================================

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
