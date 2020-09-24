#ifndef BLOCKFACE_HPP_INCLUDED
#define BLOCKFACE_HPP_INCLUDED

#include <vector>
#include <memory>

#include "../../Util/NonCopyable.hpp"
#include "../../Mesh/Mesh.hpp"
#include "../../Texture/BasicTexture.hpp"

enum class FaceID
{
	Front = 0,
	Back = 1,
	Left = 2,
	Right = 3,
	Top = 4,
	Bottom = 5
};

struct BlockFace : public NonCopyable
{
	Mesh m_mesh;
	FaceID m_side;
	BasicTexture m_texture;
};

#endif // BLOCKFACE_HPP_INCLUDED
