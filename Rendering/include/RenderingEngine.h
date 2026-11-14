#pragma once
#include <thread>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <mutex>
#include <functional>
#include <glm/glm.hpp>
#include <unordered_map>
#include "RenderCommand.h"
#include "RenderingStructs.h"
#include "Shader.h"

namespace rendering {

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

        void loadShaders();


        void processDirtyEnts();

        void updateRenderCommand(const RenderingEntity& entity, RenderCommand& command);
        void createRenderCommand(const RenderingEntity& entity);
        GLFWwindow* m_window = nullptr;

        std::atomic<bool>m_shouldStop{ false };
        std::atomic<bool>m_isInitialized{ false };
        std::atomic<bool>m_isDirtyEnts{ false };

        std::thread m_renderingThread;
        std::mutex m_RenderingMutex;

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        std::vector<RenderingEntity> m_dirtyEnts;
        std::unordered_map<uint32_t, RenderCommand> m_renderedEnts;

        //Shaders
        std::shared_ptr<Shader> m_defaultShader;
        float m_aspectRatio = 1.0f; // Default aspect ratio
        
    };
}