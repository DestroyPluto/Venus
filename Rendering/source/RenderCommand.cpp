#include "RenderCommand.h"
#include "Geometry.h"

using namespace rendering;

RenderCommand::RenderCommand(const RenderingEntity entity, std::weak_ptr<Shader> shader){
    m_globalID = entity.id;
    m_modelMatrix = glm::mat4(1.0f);
    m_shader = shader;
    //the command owns the geometry.
    m_geometry = std::make_unique<Geometry>(m_globalID);
    //TODO make it so you can pass in any vertex data.
    m_geometry->addAttribute(0, m_DefaultVertexData, 3);
}

void RenderCommand::execute() {
    //only render if there is a valid shader to use.
    if (auto shader = m_shader.lock()) {
        shader->Bind();
        m_geometry->drawGeometry();
        shader->Unbind();
    }
}
