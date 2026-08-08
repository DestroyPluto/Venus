#include <iostream>
#include "RenderingEngine.h"
#include <memory>
#include <thread>


using namespace rendering;

class Game {
public:
    Game() {
        m_renderingEngine = std::make_shared<RenderingEngine>();

    };

    void run() {
        bool shouldExit = false;
        
       
        //while(!shouldExit) {
            //update game
        //}

        m_renderingEngine->close();
    }

    std::shared_ptr<RenderingEngine> m_renderingEngine;
};

int main(int argc, char** argv) {
    Game game;
    game.run();
    return 0;
}