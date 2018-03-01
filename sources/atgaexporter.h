#ifndef SPCWAD_ATGAEXPORTER_H
#define SPCWAD_ATGAEXPORTER_H

//=============================================================================

#include <string>

//=============================================================================

namespace spcWAD
{

//=============================================================================

class ATGAExporter
{
public:
	bool exportData(const std::string& fileName, unsigned char *data, const int width, const int height);

private:
	bool RGB2BGR(unsigned char* data, int width, int height);
	bool flipOver(unsigned char* data, int width, int height);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ATGAEXPORTER_H
