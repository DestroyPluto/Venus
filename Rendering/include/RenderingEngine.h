#pragma once
#include <thread>
#include <GLFW/glfw3.h>
#include <mutex>
#include <functional>


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

    private:
        void start();
        void renderLoop();

        GLFWwindow* m_window = nullptr;

        std::atomic<bool>m_shouldStop{ false };
        std::atomic<bool>m_isInitialized{ false };

        std::thread m_renderingThread;
        std::mutex m_RenderingMutex;

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    };
}