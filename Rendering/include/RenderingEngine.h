#pragma once
#include <thread>
#include <GLFW/glfw3.h>

namespace rendering {
    class RenderingEngine {
    public:
        RenderingEngine();
        void start();
        void close();
    private:
        void renderLoop();
        GLFWwindow* m_window;
        std::thread m_renderingThread;
    };
}