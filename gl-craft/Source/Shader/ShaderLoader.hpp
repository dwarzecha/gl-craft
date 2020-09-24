#ifndef SHADERLOADER_HPP_INCLUDED
#define SHADERLOADER_HPP_INCLUDED

#include <iostream>
#include <string>

#include "GL/glew.h"

namespace ShaderLoader
{
    unsigned int CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str(); // Make sure source exists!
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        
        // Error checking
        int status;
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE)
        {
            std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader compilation failed!\n";
            exit(EXIT_FAILURE);
        }
        
        return id;
    }
    
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        
        glLinkProgram(program);
        glValidateProgram(program);
        
        glDeleteShader(vs);
        glDeleteShader(fs);
        
        return program;
    }
};

#endif // SHADERLOADER_HPP_INCLUDED
