#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED

#include <string>

#include "SFML/Window.hpp"

struct Context
{
	Context(std::string name);

	sf::Window window;
};

#endif // CONTEXT_HPP_INCLUDED