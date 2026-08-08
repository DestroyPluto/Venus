#include "RenderingEngine.h"

using namespace rendering;

RenderingEngine::RenderingEngine() {
    m_renderingThread = std::thread(&RenderingEngine::start, this);

}

void RenderingEngine::start() {
    // Rendering loop

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

}

void RenderingEngine::renderLoop() {
    while (!glfwWindowShouldClose(m_window)) {
        // Rendering code here
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void RenderingEngine::close() {
    if (m_renderingThread.joinable()) {
        glfwTerminate();
        m_renderingThread.join();
    }
}