#include <iostream>

#include "GL/glew.h"
#include "SFML/Graphics.hpp"

#include "BasicTexture.hpp"

BasicTexture::BasicTexture(const std::string& file)
{
    LoadFromFile(file);
}

void BasicTexture::LoadFromFile(const std::string& file)
{
    sf::Image img;
    
    if (!img.loadFromFile("Res/Textures/Blocks/" + file))
    {
		// TODO: Throw error
    }
    
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
}

void BasicTexture::BindTexture()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

BasicTexture::~BasicTexture()
{
	Release();
}

void BasicTexture::Release()
{
	glDeleteTextures(1, &m_id);
	m_id = 0;
}
