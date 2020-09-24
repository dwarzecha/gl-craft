#include "GL/glew.h"

#include "Shader.hpp"

void Shader::UniformMatrix4fv(glm::mat4 value, const std::string& name) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Shader::GetShaderProgram() const
{
    return m_shaderProgram;
}


