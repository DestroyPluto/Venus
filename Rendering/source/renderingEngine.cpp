#include "RenderingEngine.h"
#include <cassert>

using namespace rendering;

void RenderingEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    RenderingEngine* renderingEngine = static_cast<RenderingEngine*>(glfwGetWindowUserPointer(window));
    if(!renderingEngine->m_keyCallback){
        return;
    }
    renderingEngine->m_keyCallback(key, action);
}

void RenderingEngine::mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    RenderingEngine* renderingEngine = static_cast<RenderingEngine*>(glfwGetWindowUserPointer(window));
    if(!renderingEngine->m_mouseCallback){
        return;
    }

    int windowX;
    int windowY;

    glfwGetWindowSize(window, &windowX, &windowY);
    //x and y to clip coords
    float x = 2 * ((float)xPos / (float)windowX) - 1;
    float y = 2 * ((float)yPos / (float)windowY) - 1;
    y = -y;
    renderingEngine->m_mouseCallback(x, y);
}

void RenderingEngine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    RenderingEngine* renderingEngine = static_cast<RenderingEngine*>(glfwGetWindowUserPointer(window));
    if(!renderingEngine->m_mouseButtonCallback){
        return;
    }
    renderingEngine->m_mouseButtonCallback(button, action);
}

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

    m_window = glfwCreateWindow(800, 600, "Venus", NULL, NULL);

    if (m_window == NULL) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);
    
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetCursorPosCallback(m_window, mouse_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);

    glfwSetWindowUserPointer(m_window, this);

    m_isInitialized.store(true, std::memory_order_release);

    renderLoop();

    close();

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
    glfwTerminate();
    if (m_renderingThread.joinable()) {
        m_renderingThread.join();
    }
}