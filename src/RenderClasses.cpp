/*
 * RenderClasses.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#include "RenderClasses.hpp"
#include "TetrisUtils.hpp"
#include <vector>
#include <iostream>


RenderClass::RenderClass(TetrisGrid& w_tetrisGrid, sf::RenderWindow& w_gameWindow) : m_tetrisGrid(w_tetrisGrid), m_gameWindow(w_gameWindow)
{
    m_tileTextures.resize(7);
    m_tileTextures[1].loadFromFile("../textures/blue.png");
    m_tileTextures[2].loadFromFile("../textures/red.png");
    m_tileTextures[3].loadFromFile("../textures/lblue.png");
    m_tileTextures[4].loadFromFile("../textures/cyan.png");
    m_tileTextures[5].loadFromFile("../textures/green.png");
    m_tileTextures[6].loadFromFile("../textures/pink.png");
}


RenderClass::~RenderClass()
{

}

void RenderClass::updateGraphics()
{
    m_tileSprites.clear();
    for(uint32_t row = 0; row < m_tetrisGrid.getRows(); row++)
    {
        for(uint32_t col = 0; col < m_tetrisGrid.getCols(); col++)
        {
            BlockColor currColor = m_tetrisGrid.getTileColor(row, col);
            if(currColor != cEmpty)
            {
                sf::Sprite sprite;
                sprite.setTexture(m_tileTextures[currColor]);
                sprite.setPosition(sf::Vector2f(24 * row, 24 * col));
                m_tileSprites.push_back(sprite);
                std::cout << "pushing back" << std::endl;
            }
        }
    }
    for(auto it = m_tileSprites.begin(); it != m_tileSprites.end(); it++)
    {
        m_gameWindow.draw(*it);
    }
}
