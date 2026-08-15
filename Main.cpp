#include <iostream>
#include "RenderingEngine.h"
#include "Keyboard.h"
#include <memory>
#include <thread>
#include <chrono>

using namespace rendering;
using namespace engine;

class Game {
public:

    Game() {
        m_renderingEngine = std::make_shared<RenderingEngine>();
        m_keyboard = std::make_shared<Keyboard>();

        m_renderingEngine->setKeyCallback([this](int key, int action) {
            printf("Key callback: key=%d, action=%d\n", key, action);
            m_keyboard->setKey(key, action);
        });
        
        //dummy entity for testing
        m_entity = RenderingEntity {
            1,
            ENTITY_TYPE_GAME_OBJECT,
            "",
            {
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0f, 1.0f)
            }
        };
    }

    void run() {
        bool shouldExit = false;
        
        //wait for rendering engine to initialize
        while (!m_renderingEngine->isInitialized()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        m_renderingEngine->setDirtyEnts({m_entity});

        while(!shouldExit) {
            shouldExit = m_renderingEngine->shouldStop();

            if (m_keyboard->getKeyPressed(Keyboard::KEY_ESCAPE)) {
                shouldExit = true;
            }
            //update game

        }

        printf("running main thread with id: %ld\n", std::this_thread::get_id()._Get_underlying_id());


        m_renderingEngine->close();

        printf("rendering thread closed\n");
    }

private:

    std::shared_ptr<RenderingEngine> m_renderingEngine;
    std::shared_ptr<Keyboard> m_keyboard;
    RenderingEntity m_entity;

};

int main(int argc, char** argv) {
    Game game;
    game.run();
    return 0;
}