#include "ChunkRenderer.hpp"

#include "GL/glew.h"

#include "../Texture/TexturePaths.hpp"

ChunkRenderer::ChunkRenderer(std::shared_ptr<Chunk> chunk)
{
	Add(chunk);
}

void ChunkRenderer::Add(std::shared_ptr<Chunk> chunk)
{
	m_chunks.push_back(chunk);
}

void ChunkRenderer::DrawQuads(const unsigned int& shaderProgram)
{
	while (!m_chunks.empty())
	{
		const std::vector<std::shared_ptr<ChunkSection> > tempSections = m_chunks.back()->GetSections();

		for (auto& section : tempSections)
		{
			if (section != nullptr)
			{
				section->Bind();

				glm::mat4 model = glm::mat4(1.0);
				model = glm::translate(model, m_chunks.back()->GetPos() + section->GetPos());

				int uniModel = glGetUniformLocation(shaderProgram, "model");
				glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

				std::vector<std::unique_ptr<BlockFace> >* tempFaces = section->GetFaces();

				for (int i = 0; i < tempFaces->size(); i++)
				{
					tempFaces->at(i)->m_texture.BindTexture();
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(i * 6 * sizeof(unsigned int)));
				}
			}
		}

		m_chunks.pop_back();
	}
}