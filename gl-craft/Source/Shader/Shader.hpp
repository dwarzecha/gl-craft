#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../Util/NonCopyable.hpp"

class Shader : public NonCopyable
{
public:
	virtual ~Shader() = default;
    void UniformMatrix4fv(glm::mat4 value, const std::string& name) const;
    unsigned int GetShaderProgram() const;
    
protected:
    unsigned int m_shaderProgram;
};

#endif // SHADER_HPP_INCLUDED
