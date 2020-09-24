#ifndef BASICTEXTURE_HPP_INCLUDED
#define BASICTEXTURE_HPP_INCLUDED

#include <string>

#include "../Util/NonCopyable.hpp"

class BasicTexture : public NonCopyable
{
public:
    BasicTexture() = default;
    BasicTexture(const std::string& file);
    ~BasicTexture();
    
    void LoadFromFile(const std::string& file);
    
    void BindTexture();
    
private:
    unsigned int m_id = 0;

	void Release();
};

#endif // BASICTEXTURE_HPP_INCLUDED
