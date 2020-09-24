#include "Block.hpp"

#include <fstream>
#include <string>

#include "BlockMesh.hpp"

Block::Block(BlockID id, glm::vec3 pos)
	: m_id(id), m_pos(pos)
{
	LoadParameters();
}

glm::vec3 Block::GetPos() const
{
	return m_pos;
}

BlockID Block::GetID() const
{
	return m_id;
}

float Block::GetOpacity() const
{
	return m_opacity;
}

void Block::SetPos(glm::vec3 pos)
{
	m_pos = pos;
}

void Block::SetID(BlockID id)
{
	m_id = id;
	LoadParameters();
}

void Block::LoadParameters()
{
	std::ifstream blockDatabase;

	std::string params;

	blockDatabase.open("Res/BlockDatabase.txt");

	bool foundParams = false;

	while (foundParams == false)
	{
		std::getline(blockDatabase, params, ' ');

		if (std::stoi(params) == static_cast<int>(m_id))
		{
			std::getline(blockDatabase, params, ' ');
			m_collidable = params == "1";

			std::getline(blockDatabase, params, ' ');
			m_opacity = std::stof(params);

			foundParams = true;
		}
		else
		{
			blockDatabase.ignore(10, '\n');
		}
	}

	blockDatabase.close();
}