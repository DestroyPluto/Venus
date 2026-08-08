#include <iostream>
#include "RenderingEngine.h"
#include <memory>
#include <thread>
#include <chrono>

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
        printf("running main thread with id: %ld\n", std::this_thread::get_id()._Get_underlying_id());


        std::this_thread::sleep_for(std::chrono::seconds(2));

        m_renderingEngine->close();

        printf("rendering thread closed\n");
    }
private:
    std::shared_ptr<RenderingEngine> m_renderingEngine;

};

int main(int argc, char** argv) {
    Game game;
    game.run();
    return 0;
}