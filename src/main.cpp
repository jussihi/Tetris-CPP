#include "graphics.hpp"
#include "TetrisClasses.hpp"
#include "RenderClasses.hpp"
#include <iostream>


static GameState gameState = sPlay;

static const double cFPS = 60;
static const double cDeltaTime = 1 / cFPS;

static const double cTickRate = 1.0 / 100.0;



int main(void)
{
    sf::RenderWindow gameWindow(sf::VideoMode(1410, 960), "Classic tetris");
    gameWindow.setFramerateLimit(60);



    // initialize game params here
    TetrisGrid tetrisGrid(20, 10);
    TetrisGame* tetrisGame = new TetrisGame(tetrisGrid, cDeltaTime);

    double lastTick = 0.0;
    double lastRender = 0.0;
    double currTime = 0.0;

    sf::Clock tickClock;
    //sf::Clock gfxClock;

    uint32_t offsetX = 33;
    uint32_t offsetY = 194;

    RenderClass renderer1(tetrisGrid, gameWindow, offsetX, offsetY, true);

    int32_t movementHorizontal = 0;
    int32_t rotation = 0;

    bool softDrop = false;

    while(gameWindow.isOpen())
    {
        sf::Event event;
        bool setSoft = false;
        while(gameWindow.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyPressed:
                {
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Left:
                            movementHorizontal--;
                            break;
                        case sf::Keyboard::Right:
                            movementHorizontal++;
                            break;
                        case sf::Keyboard::A:
                            rotation--;
                            break;
                        case sf::Keyboard::X:
                            rotation++;
                            break;
                        case sf::Keyboard::Down:
                            setSoft = true;
                            break;
                    }
                    break;
                }
                case sf::Event::Closed:
                    gameState = sQuit;
                    break;
                default:
                    break;
            }
        }

        softDrop = setSoft;


        if(gameState == sPlay)
        {
            tetrisGame->tick(movementHorizontal, rotation, softDrop);
            renderer1.updateGraphics();
            movementHorizontal = 0;
            rotation = 0;
        }

        if(gameState == sQuit)
        {
        	break;
        }
    }

    return 0;
}
