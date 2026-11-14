#include "RenderCommand.h"
#include "Geometry.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

using namespace rendering;

RenderCommand::RenderCommand(const RenderingEntity& entity, std::weak_ptr<Shader> shader){
    m_globalID = entity.id;
    
    m_shader = shader;
    //the command owns the geometry.
    m_geometry = std::make_unique<Geometry>(m_globalID);
    //TODO make it so you can pass in any vertex data.
    m_geometry->addAttribute(0, m_DefaultVertexData, 3);
    
    update(entity);

}

void RenderCommand::update(const RenderingEntity& entity) {
    m_modelMatrix = glm::mat4(1.0f);
    m_modelMatrix = glm::translate(m_modelMatrix, entity.transform.position);
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(entity.transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(entity.transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(entity.transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_modelMatrix = glm::scale(m_modelMatrix, entity.transform.scale);
    if (auto shader = m_shader.lock()) {
        shader->setUniform("colour", entity.colour);
        shader->setUniform("model", m_modelMatrix);
    }
}

void RenderCommand::execute() {
    //only render if there is a valid shader to use.
    if (auto shader = m_shader.lock()) {
        shader->Bind();
        m_geometry->drawGeometry();
        shader->Unbind();
    }
}
