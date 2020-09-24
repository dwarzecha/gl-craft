#include "TexturePaths.hpp"

namespace TexturePaths
{
	PathMap grass = {
		{0, "Grass/Side1.png"},
		{1, "Grass/Side2.png"},
		{2, "Grass/Side3.png"},
		{3, "Grass/Side4.png"},
		{4, "Grass/Top.png"},
		{5, "Grass/Bottom.png"}
	};

	PathMap dirt = {
		{0, "Dirt/Side1.png"},
		{1, "Dirt/Side2.png"},
		{2, "Dirt/Side3.png"},
		{3, "Dirt/Side4.png"},
		{4, "Dirt/Top.png"},
		{5, "Dirt/Bottom.png"}
	};

	PathMap stone = {
		{0, "Stone/Side1.png"},
		{1, "Stone/Side2.png"},
		{2, "Stone/Side3.png"},
		{3, "Stone/Side4.png"},
		{4, "Stone/Top.png"},
		{5, "Stone/Bottom.png"}
	};

	std::vector<PathMap> paths = { grass, dirt, stone };
}