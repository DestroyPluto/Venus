#pragma once
#include <cstdint>
#include <glm/glm.hpp>

namespace rendering{

    typedef enum entityType {
        ENTITY_TYPE_GAME_OBJECT,
        ENTITY_TYPE_UI_OBJECT,
        ENTITY_TYPE_BACKGROUND_OBJECT
    } EntityType;

    typedef struct Transform {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    } Transform;

    typedef struct RenderingEntity {
        uint32_t id;
        EntityType type;
        const char* TexturePath;
        Transform transform;
    } RenderingEntity;

}