#include "BasicShader.hpp"
#include "ShaderLoader.hpp"
#include "ShaderSource.hpp"

BasicShader::~BasicShader()
{
	glDeleteProgram(m_shaderProgram);
}

void BasicShader::LoadShader()
{
    m_shaderProgram = ShaderLoader::CreateShader(vertexSource, fragmentSource);
    glUseProgram(m_shaderProgram);
}
