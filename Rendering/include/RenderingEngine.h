#pragma once
#include <thread>
#include <GLFW/glfw3.h>
#include <mutex>
#include <functional>
#include <glm/glm.hpp>

namespace rendering {

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

    class RenderingEngine {
    public:
        RenderingEngine();
        void close();
        virtual ~RenderingEngine();
        bool isInitialized() const { return m_isInitialized.load(std::memory_order_acquire); }

        std::function<void(int, int)> m_keyCallback;
        std::function<void(double, double)> m_mouseCallback;
        std::function<void(int, int)> m_mouseButtonCallback;

        void setKeyCallback(std::function<void(int, int)> callback) { m_keyCallback = std::move(callback); }
        void setMouseCallback(std::function<void(double, double)> callback) { m_mouseCallback = std::move(callback); }
        void setMouseButtonCallback(std::function<void(int, int)> callback) { m_mouseButtonCallback = std::move(callback); }
        bool shouldStop() const { return m_shouldStop.load(std::memory_order_acquire); }
        void setDirtyEnts(std::vector<RenderingEntity> dirtyEnts);
    private:
        void start();
        void renderLoop();

        void processDirtyEnts();

        GLFWwindow* m_window = nullptr;

        std::atomic<bool>m_shouldStop{ false };
        std::atomic<bool>m_isInitialized{ false };
        std::atomic<bool>m_isDirtyEnts{ false };

        std::thread m_renderingThread;
        std::mutex m_RenderingMutex;

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        
        std::vector<RenderingEntity> m_dirtyEnts;
        
    };
}