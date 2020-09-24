#include "Context.hpp"
#include "GL/glew.h"

Context::Context(std::string name)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.antialiasingLevel = 4;

	window.create(sf::VideoMode(800, 600), name, sf::Style::Titlebar | sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorGrabbed(true);
	window.setMouseCursorVisible(false);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
}