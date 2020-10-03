#include "ChunkSection.hpp"

#include "../WorldConstants.hpp"

ChunkSection::ChunkSection(glm::vec3 pos)
	: m_pos(pos)
{
	m_generator.SetSize(SECTION_SIZE);
	m_model = std::make_unique<Model>();
}

void ChunkSection::AddBlock(std::shared_ptr<Block> block)
{
	m_generator.AddBlock(block);
}

void ChunkSection::LoadSurrounding(const std::vector<std::shared_ptr<Block> >* surroundingBlocks, int dirIter)
{
	m_generator.LoadSurrounding(surroundingBlocks, dirIter);
}

void ChunkSection::CreateModel()
{
	m_model = m_generator.GenerateModel();
}

void ChunkSection::Bind()
{
	m_model->BindVAO();
}

glm::vec3 ChunkSection::GetPos()
{
	return m_pos;
}

std::shared_ptr<Block> ChunkSection::GetBlock(glm::vec3 pos) const
{
	std::shared_ptr<Block> block = m_generator.GetBlock(ChunkToSectionCoords(pos));
	if (block != nullptr) block->SetPos(pos);

	return block;
}

std::vector<std::unique_ptr<BlockFace> >* ChunkSection::GetFaces()
{
	return m_generator.GetFaces();
}

const std::vector<std::shared_ptr<Block> >* ChunkSection::GetBlocks() const
{
	return m_generator.GetBlocks();
}

void ChunkSection::SetBlock(glm::vec3 pos, BlockID id)
{
	m_generator.SetBlock(ChunkToSectionCoords(pos), id);
}

int ChunkSection::OnBorder() const
{
	if (m_pos.x == 0.0f) return 2;
	if (m_pos.z == 0.0f) return 0;
	if (m_pos.x == CHUNK_SIZE - 1.0f) return 3;
	if (m_pos.z == CHUNK_SIZE - 1.0f) return 1;

	return -1;
}

glm::vec3 ChunkSection::ChunkToSectionCoords(glm::vec3 pos) const
{
	return pos - m_pos;
}

glm::vec3 ChunkSection::SectionToChunkCoords(glm::vec3 pos) const
{
	return pos + m_pos;
}