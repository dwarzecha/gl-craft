#ifndef CHUNKMODELGENERATOR_HPP_INCLUDED
#define CHUNKMODELGENERATOR_HPP_INCLUDED

#include <vector>

#include "glm/glm.hpp"

#include "../../Util/NonCopyable.hpp"
#include "../Block/Block.hpp"
#include "../../Model/Model.hpp"

class ChunkModelGenerator : public NonCopyable
{
public:
	ChunkModelGenerator();

	void LoadSurrounding(const std::vector<std::shared_ptr<Block> >* surroundingBlocks, int dirIter);

	std::unique_ptr<Model> GenerateModel();

	void AddBlock(std::shared_ptr<Block> block);

	std::vector<std::unique_ptr<BlockFace> >* GetFaces();
	const std::vector<std::shared_ptr<Block> >* GetBlocks() const;
	std::shared_ptr<Block> GetBlock(glm::vec3 pos) const;

	void SetBlock(glm::vec3 pos, BlockID id);
	void SetSize(int size);

private:
	void CreateFaces();
	
	int GetIndex(glm::vec3 pos) const;
	bool CheckBlock(std::shared_ptr<Block> b, int dirIter);
	bool OutOfBounds(glm::vec3 pos);
	void AddFaceToMesh(std::vector<float> face, glm::vec3 pos);

	std::vector<std::unique_ptr<BlockFace> > m_faces;
	std::vector<std::shared_ptr<Block> > m_blocks;

	std::vector<const std::vector<std::shared_ptr<Block> >* > m_surroundingBlocks;

	int m_size;
};

#endif // CHUNKMODELGENERATOR_HPP_INCLUDED
