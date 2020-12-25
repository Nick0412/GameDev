#ifndef VERTEX_MODEL_H
#define VERTEX_MODEL_H

#include "glad/glad.h"

#include <vector>

namespace CoreGL
{
    class VertexModel
    {
    private:
        GLuint m_vao_id;
        std::vector<GLuint> m_indicies;
    public:
        VertexModel();
        ~VertexModel() = default;
        VertexModel(const VertexModel& rhs) = delete;
        VertexModel(VertexModel&& rhs) = delete;
        VertexModel& operator=(const VertexModel& rhs) = delete;
        VertexModel& operator=(VertexModel&& rhs) = delete;

        void storeDataInAttribute(const GLuint attribute_index, const GLuint attribute_size, const std::vector<GLfloat>& data) const;
        void storeIndexData(const std::vector<GLuint>& indicies);
        void bind() const;
        void unbind() const;
        void draw() const;
    };
}

#endif