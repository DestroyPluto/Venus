#include "RenderCommand.h"
#include "Geometry.h"

using namespace rendering;

RenderCommand::RenderCommand(const RenderingEntity entity){
    m_globalID = entity.id;
    m_modelMatrix = glm::mat4(1.0f);
    //the command owns the geometry.
    m_geometry = std::make_unique<Geometry>(m_globalID);
    //TODO make it so you can pass in any vertex data.
    m_geometry->addAttribute(0, m_DefaultVertexData, 3);
}

void RenderCommand::execute() {
    //TODO: shader
    m_geometry->drawGeometry();

}
