#ifndef TEXTUREPATHS_HPP_INCLUDED
#define TEXTUREPATHS_HPP_INCLUDED

#include <vector>
#include <map>
#include <string>

namespace TexturePaths
{
	typedef std::map<int, std::string> PathMap;

	extern PathMap grass;
	extern std::vector<PathMap> paths;
}

#endif // TEXTUREPATHS_HPP_INCLUDED
