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

    // initialize game params here
    TetrisGrid tetrisGrid(20, 10);
    TetrisGame* tetrisGame = new TetrisGame(tetrisGrid, cTickRate);

    double lastTick = 0.0;
    double lastRender = 0.0;
    double currTime = 0.0;

    sf::Clock tickClock;
    sf::Clock gfxClock;

    uint32_t offsetX = 33;
    uint32_t offsetY = 194;

    RenderClass renderer1(tetrisGrid, gameWindow, offsetX, offsetY, true);

    int32_t movementHorizontal = 0;
    int32_t rotation = 0;

    while(gameWindow.isOpen())
    {
        sf::Event event;
        while(gameWindow.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyPressed:
                {
                    std::cout << "Key pressed" << std::endl;
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Left:
                            movementHorizontal--;
                            std::cout << "it was left" << std::endl;
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


        if(gameState == sPlay)
        {
            if(tickClock.getElapsedTime().asSeconds() >= cTickRate)
            {
                tickClock.restart();
                tetrisGame->tick(movementHorizontal, rotation);
                movementHorizontal = 0;
                rotation = 0;
            }

            // would it be better left this be as it was in the last call?
            if(gfxClock.getElapsedTime().asSeconds() >= cDeltaTime)
            {
                gfxClock.restart();
                renderer1.updateGraphics();
            }
        }

        if(gameState == sQuit)
        {
            break;
        }
    }

    std::cout << "out" << std::endl;

    return 0;
}
