#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Geometry.h"
#include "RenderingStructs.h"
#include "Shader.h"

namespace rendering {

    class RenderCommand {
    public:
        RenderCommand(const RenderingEntity entity, std::weak_ptr<Shader> shader);
        void execute();

    private:
        uint32_t m_globalID;
        glm::mat4 m_modelMatrix;
        //geometry?
        std::unique_ptr<Geometry> m_geometry;
        //just a square for now.
        std::vector<float> m_DefaultVertexData {-0.5f, -0.5f, 1.0f,
                                                -0.5f,  0.5f, 1.0f, 
                                                 0.5f,  0.5f, 1.0f, 
        
                                                -0.5f, -0.5f, 1.0f, 
                                                 0.5f,  0.5f, 1.0f, 
                                                 0.5f, -0.5f, 1.0f};

    std::weak_ptr<Shader> m_shader;
    };
   
}