#pragma once
#include <thread>
#include <GLFW/glfw3.h>
#include <mutex>
namespace rendering {
    class RenderingEngine {
    public:
        RenderingEngine();
        void close();
        virtual ~RenderingEngine();
    private:
        void start();
        void renderLoop();
        GLFWwindow* m_window = nullptr;
        std::thread m_renderingThread;
        std::mutex m_RenderingMutex;
        std::atomic<bool>m_shouldStop {false};
    };
}