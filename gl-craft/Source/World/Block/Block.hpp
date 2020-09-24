#ifndef BLOCK_HPP_INCLUDED
#define BLOCK_HPP_INCLUDED

#include <vector>
#include <memory>

#include "glm/glm.hpp"

#include "../../Model/Model.hpp"
#include "BlockFace.hpp"
#include "BlockID.hpp"

class Block
{
public:
	Block() = default;
	Block(BlockID id, glm::vec3 pos);

	glm::vec3 GetPos() const;
	BlockID GetID() const;
	float GetOpacity() const;

	void SetPos(glm::vec3 pos);
	void SetID(BlockID id);

private:
	void LoadParameters();

	BlockID m_id;
	glm::vec3 m_pos;
	bool m_collidable;
	float m_opacity;
};

#endif // BLOCK_HPP_INCLUDED

