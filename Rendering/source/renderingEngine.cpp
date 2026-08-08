#include "RenderingEngine.h"

using namespace rendering;

RenderingEngine::RenderingEngine() {
    m_renderingThread = std::thread(&RenderingEngine::start, this);
}

void RenderingEngine::start() {
    // Rendering loop
    printf("Starting Rendering thread with id: %ld\n", std::this_thread::get_id()._Get_underlying_id());

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(800.0f, 600.0f, "Venus", NULL, NULL);

    if (m_window == NULL) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);

    renderLoop();

    glfwTerminate();

}

void RenderingEngine::renderLoop() {
    while (!glfwWindowShouldClose(m_window)) {
        if (m_shouldStop.load(std::memory_order_acquire)) {
            glfwSetWindowShouldClose(m_window, true);
            continue;
        }
        
        // Rendering code here
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void RenderingEngine::close() {
    m_shouldStop.store(true, std::memory_order_release);
}

RenderingEngine::~RenderingEngine() {
    if (m_renderingThread.joinable()) {
        m_renderingThread.join();
    }
}