#include "ChunkModelGenerator.hpp"

#include <memory>

#include "../Block/BlockMesh.hpp"
#include "../../Direction/Direction.hpp"
#include "../../Texture/TexturePaths.hpp"

ChunkModelGenerator::ChunkModelGenerator()
{
	m_surroundingBlocks.resize(6);
}

void ChunkModelGenerator::LoadSurrounding(const std::vector<std::shared_ptr<Block> >* surroundingBlocks, int dirIter)
{
	m_surroundingBlocks.at(dirIter) = surroundingBlocks;
}

std::unique_ptr<Model> ChunkModelGenerator::GenerateModel()
{
	std::unique_ptr<Model> tempModel = std::make_unique<Model>();

	CreateFaces();

	Mesh tempMesh;

	for (const auto& face : m_faces)
	{
		tempMesh.vertices.insert( tempMesh.vertices.end(),
								  face->m_mesh.vertices.begin(),
								  face->m_mesh.vertices.end());
		tempMesh.texCoords.insert( tempMesh.texCoords.end(),
								   face->m_mesh.texCoords.begin(),
								   face->m_mesh.texCoords.end() );
		tempMesh.indices.insert( tempMesh.indices.end(),
								 face->m_mesh.indices.begin(),
								 face->m_mesh.indices.end() );
	}

	tempModel->AddData(tempMesh);
	return std::move(tempModel);
}

void ChunkModelGenerator::AddBlock(std::shared_ptr<Block> block)
{
	m_blocks.push_back(block);
}

std::shared_ptr<Block> ChunkModelGenerator::GetBlock(glm::vec3 pos) const
{
	return m_blocks.at(GetIndex(pos));
}

void ChunkModelGenerator::CreateFaces()
{
	m_faces.clear();

	for (auto block : m_blocks)
	{
		if (block != nullptr && block->GetOpacity() > 0.0f)
		{
			for (int j = 0; j < 6; j++)
			{
				if (CheckBlock(block, j))
				{
					AddFaceToMesh(BlockMesh::faces.at(j), block->GetPos());
					m_faces.back()->m_side = static_cast<FaceID>(j);
					m_faces.back()->m_texture
					.LoadFromFile( TexturePaths::paths.at( static_cast<int>(block->GetID()) ).at(j) );
				}
			}
		}
	}
}

int ChunkModelGenerator::GetIndex(glm::vec3 pos) const
{
	return (pos.x) * m_size * m_size + (pos.y) * m_size + (pos.z);
}

bool ChunkModelGenerator::CheckBlock(std::shared_ptr<Block> b, int dirIter)
{
	glm::vec3 dir = Direction::directions.at(dirIter);
	glm::vec3 pos = b->GetPos();

	if (OutOfBounds(pos + dir))
	{
		const std::vector<std::shared_ptr<Block> >* blocks = m_surroundingBlocks.at(dirIter);

		if ((pos + dir).x < 0.0f) pos.x = m_size - 1.0f;
		if ((pos + dir).y < 0.0f) pos.y = m_size - 1.0f;
		if ((pos + dir).z < 0.0f) pos.z = m_size - 1.0f;

		if ((pos + dir).x > static_cast<float>(m_size) - 1.0f) pos.x = 0.0f;
		if ((pos + dir).y > static_cast<float>(m_size) - 1.0f) pos.y = 0.0f;
		if ((pos + dir).z > static_cast<float>(m_size) - 1.0f) pos.z = 0.0f;

		//if (blocks == nullptr && dirIter != 4)
		//{
		//	return false;
		//}

		if (blocks == nullptr ||
			(blocks->at(GetIndex(pos)) == nullptr || blocks->at(GetIndex(pos))->GetOpacity() != 1.0f))
		{
			return true;
		}

		return false;
	}

	if (m_blocks.at(GetIndex(pos + dir)) == nullptr || m_blocks.at(GetIndex(pos + dir))->GetOpacity() != 1.0f) return true;

	return false;
}

bool ChunkModelGenerator::OutOfBounds(glm::vec3 pos)
{
	if (pos.x < 0.0f) return true;
	if (pos.y < 0.0f) return true;
	if (pos.z < 0.0f) return true;

	if (pos.x > static_cast<float>(m_size) - 1.0f) return true;
	if (pos.y > static_cast<float>(m_size) - 1.0f) return true;
	if (pos.z > static_cast<float>(m_size) - 1.0f) return true;

	return false;
}

void ChunkModelGenerator::AddFaceToMesh(std::vector<float> face, glm::vec3 pos)
{
	std::unique_ptr<BlockFace> tempFace = std::make_unique<BlockFace>();
	tempFace->m_mesh.vertices = BlockMesh::Move(face, pos);
	tempFace->m_mesh.texCoords = BlockMesh::texCoords;
	tempFace->m_mesh.indices = BlockMesh::indices;

	for (auto& index : tempFace->m_mesh.indices)
	{
		index += m_faces.size() * 4;
	}

	m_faces.push_back(std::move(tempFace));
}

std::vector<std::unique_ptr<BlockFace> >* ChunkModelGenerator::GetFaces()
{
	return &m_faces;
}

const std::vector<std::shared_ptr<Block> >* ChunkModelGenerator::GetBlocks() const
{
	return &m_blocks;
}

void ChunkModelGenerator::SetBlock(glm::vec3 pos, BlockID id)
{
	std::shared_ptr<Block>* block = &m_blocks.at(GetIndex(pos));

	if (*block != nullptr)
	{
		if (id == BlockID::Air) *block = nullptr;
		else (*block)->SetID(id);
	}
	else
	{
		*block = std::make_shared<Block>(id, pos);
	}
}

void ChunkModelGenerator::SetSize(int size)
{
	m_size = size;
}
