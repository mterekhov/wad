#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ALump::ALump(const int size, const int offset, const std::string& name, ELumpTypes type) :
                        m_size(size), m_offset(offset), m_name(name), m_type(type), m_used(false)
{
	if (m_size == 0)
	{
		m_type = LUMPTYPES_ZEROSIZE;
	}
}

//=============================================================================

ALump::~ALump()
{
}

//=============================================================================

const bool ALump::alUsed() const
{
    return m_used;
}

//=============================================================================

const int ALump::alSize() const
{
    return m_size;
}

//=============================================================================

const int ALump::alOffset() const
{
    return m_offset;
}

//=============================================================================

const std::string& ALump::alName() const
{
    return m_name;
}

//=============================================================================

const ELumpTypes ALump::alType() const
{
    return m_type;
}

//=============================================================================

bool ALump::alReadLump(FILE* wadFile, unsigned char* data)
{
    //  set cursor in right place
    if (fseek(wadFile, m_offset, SEEK_SET))
        return false;

    //  read image data
    int read = fread(data, 1, m_size, wadFile);
    if (read != m_size)
        return false;

    return true;
}

//=============================================================================

void ALump::alDestroy(unsigned char* data)
{
    if (data)
    {
        delete data;
        data = 0;
    }
}

//=============================================================================

};  //  namespace spcWAD
