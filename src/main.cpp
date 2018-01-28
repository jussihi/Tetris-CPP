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
    sf::RenderWindow gameWindow(sf::VideoMode(800, 600), "Classic tetris");

    // initialize game params here
    TetrisGrid tetrisGrid(20, 10);
    TetrisGame* tetrisGame = new TetrisGame(tetrisGrid, cTickRate);

    double lastTick = 0.0;
    double lastRender = 0.0;
    double currTime = 0.0;

    sf::Clock tickClock;
    sf::Clock gfxClock;

    RenderClass renderer(tetrisGrid, gameWindow);

    while(gameWindow.isOpen())
    {
        gameWindow.clear();
       sf::Texture tex;
       tex.loadFromFile("../textures/blue.png");

       sf::Sprite sprite;
       sprite.setTexture(tex);

       gameWindow.draw(sprite);

       sprite.setPosition(10, 10);

       gameWindow.display();

        sf::Event event;
        while(gameWindow.pollEvent(event))
        {

        }


        if(gameState == sPlay)
        {
            if(tickClock.getElapsedTime().asSeconds() >= cTickRate)
            {
                tickClock.restart();
                tetrisGame->tick();
            }

            // would it be better left this be as it was in the last call?
            if(gfxClock.getElapsedTime().asSeconds() >= cDeltaTime)
            {
                gfxClock.restart();
                renderer.updateGraphics();
            }
            gameWindow.display();
        }

        if(gameState == sQuit)
        {
            break;
        }
    }

    std::cout << "out" << std::endl;

    return 0;
}
