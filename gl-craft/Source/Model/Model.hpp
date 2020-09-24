#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include <vector>

#include "../Util/NonCopyable.hpp"
#include "../Mesh/Mesh.hpp"

class Model : public NonCopyable
{
public:
    Model() = default;
    Model(const Mesh& mesh);
    ~Model();
    
    void AddData(const Mesh& mesh);
    
    void DeleteData();
    
    void AddVBO(int dimension, const std::vector<float>& data);
    void BindVAO() const;
    
    int GetIndicesCount() const;
    
private:
    void AddEBO(std::vector<unsigned int> indices);
    
    unsigned int m_vao = 0;
    int m_vboCount = 0;
    int m_indicesCount = 0;
    std::vector<unsigned int> m_buffers;
};

#endif // MODEL_HPP_INCLUDED
