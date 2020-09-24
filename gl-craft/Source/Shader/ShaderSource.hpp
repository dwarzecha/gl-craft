#ifndef SHADERSOURCE_HPP_INCLUDED
#define SHADERSOURCE_HPP_INCLUDED

static const char *vertexSource = R"(
#version 330 core
    
layout(location=0) in vec3 position;
layout(location=1) in vec2 texcoords;

out vec2 Texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    Texcoords = texcoords;
    gl_Position = proj * view * model * vec4(position, 1.0);
})";

static const char *fragmentSource = R"(
#version 330 core

in vec2 Texcoords;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
    outColor = texture(tex, Texcoords);
})";

#endif // SHADERSOURCE_HPP_INCLUDED
