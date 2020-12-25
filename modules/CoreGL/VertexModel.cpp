#include "VertexModel.h"

namespace CoreGL
{
    VertexModel::VertexModel()
    {
        glCreateVertexArrays(1, &m_vao_id);
    }

    void VertexModel::storeDataInAttribute(const GLuint attribute_index, const GLuint attribute_size, const std::vector<GLfloat>& data) const
    {
        // Create a buffer and specify the data in it.
        GLuint vbo_id{0};
        glCreateBuffers(1, &vbo_id);
        glNamedBufferData(vbo_id, sizeof(GLfloat)*data.size(), data.data(), GL_DYNAMIC_STORAGE_BIT);

        // Associate the buffer with a binding point.
        glVertexArrayVertexBuffer(m_vao_id, 0, vbo_id, 0, 0);

        // Enable a vertex attribute and specify the format of the data.
        // Note: this does not load any data yet, only specifies what the data format is.
        glEnableVertexArrayAttrib(m_vao_id, attribute_index);
        glVertexArrayAttribFormat(m_vao_id, attribute_index, attribute_size, GL_FLOAT, GL_FALSE, 0);

        // lastly associate the attribute index with the binding point. 
        // This is essentially how the data gets loaded into an attribute.
        glVertexArrayAttribBinding(m_vao_id, attribute_index, 0);
    }

    void VertexModel::storeIndexData(const std::vector<GLuint>& indicies)
    {
        // Create an element (also called index) buffer and specify index data in it.
        GLuint ebo_id{0};
        glCreateBuffers(1, &ebo_id);
        glNamedBufferData(ebo_id, sizeof(GLuint)*indicies.size(), indicies.data(), GL_DYNAMIC_STORAGE_BIT);

        // Set the element buffer associated with the vao. 
        // The element buffer is a special buffer and does not need a bidning point or format specification.
        glVertexArrayElementBuffer(m_vao_id, ebo_id);

        // TODO: This copy assignment can be expensive if the vector is too long. Re-design later.
        m_indicies = indicies;
    }

    void VertexModel::bind() const
    {
        glBindVertexArray(m_vao_id);
    }

    void VertexModel::unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexModel::draw() const
    {
        glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, m_indicies.data());
    }

}