#include "Geometry.h"
#include "glad/glad.h"

using namespace rendering;
Geometry::Geometry(uint32_t globalID) : m_globalID(globalID) {
    glGenVertexArrays(1, &m_vaoID);
    m_vertexCount = 0;
}

void Geometry::addAttribute(uint32_t index, std::vector<float> attribData, uint32_t components) {
    if (attribData.empty() || components == 0) {
        return;
    }

    //assume vertex is always index 0 - should hardcode/bake it in at some point.
    if (index == 0) {
        m_vertexCount = static_cast<uint32_t>(attribData.size() / components);
    }

    glBindVertexArray(m_vaoID);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, attribData.size() * sizeof(float), attribData.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(static_cast<GLuint>(index), components, GL_FLOAT, GL_FALSE, components * sizeof(float), (void*)0);
    glEnableVertexAttribArray(static_cast<GLuint>(index));
    
    //reset state
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void Geometry::drawGeometry() {
    if (m_vertexCount == 0) {
        return;
    }
    glBindVertexArray(m_vaoID);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);

    glBindVertexArray(0);
}