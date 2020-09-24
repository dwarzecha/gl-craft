#include "Model.hpp"

#include "GL/glew.h"

Model::Model(const Mesh& mesh)
{
    AddData(mesh);
}

Model::~Model()
{
    DeleteData();
}

void Model::AddData(const Mesh& mesh)
{
    if (m_vao != 0)
    {
        DeleteData();
    }
    
    m_indicesCount = mesh.indices.size();
    
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    AddVBO(3, mesh.vertices);
    AddVBO(2, mesh.texCoords);
    AddEBO(mesh.indices);
}

void Model::DeleteData()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(m_buffers.size(), m_buffers.data());
    
    m_buffers.clear();
    
    m_vao = 0;
    m_vboCount = 0;
    m_indicesCount = 0;
}

void Model::AddVBO(int dimension, const std::vector<float> &data)
{
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_vboCount, dimension, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    glEnableVertexAttribArray(m_vboCount++);
    
    m_buffers.push_back(vbo);
}

void Model::BindVAO() const
{
    glBindVertexArray(m_vao);
}

int Model::GetIndicesCount() const
{
    return m_indicesCount;
}

void Model::AddEBO(std::vector<unsigned int> indices)
{
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);
    
    m_buffers.push_back(ebo);
}
