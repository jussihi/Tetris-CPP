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

    int i = 0;
    for(uint32_t col = 0; col < m_tetrisGrid.getCols(); col++)
    {
        for(uint32_t row = 0; row < m_tetrisGrid.getRows(); row++)
        {
            BlockColor currColor = m_tetrisGrid.getTileColor(row, col);
            if(currColor != cEmpty)
            {
                i++;
                sf::Sprite sprite;
                sprite.setTexture(m_tileTextures[currColor]);
                sprite.setPosition(sf::Vector2f(24 * col, 24 * row));
                m_tileSprites.push_back(sprite);
            }
        }
    }

    BlockBody currBody = m_tetrisGrid.getCurrBlock().getBody();
    BlockColor currColor = m_tetrisGrid.getCurrBlock().getColor();

    for(uint32_t blockCol = 0; blockCol < currBody[0].size(); blockCol++)
    {
        for(uint32_t blockRow = 0; blockRow < currBody.size(); blockRow++)
        {
            if(currBody[blockCol][blockRow] != cEmpty)
            {
                i++;
                sf::Sprite sprite;
                sprite.setTexture(m_tileTextures[currColor]);
                sprite.setPosition(sf::Vector2f(24.0 * (blockCol + m_tetrisGrid.getCurrBlockCol()), 24.0 * (blockRow + m_tetrisGrid.getCurrBlockRow())));
                m_tileSprites.push_back(sprite);
            }
        }
    }

    // update screen
    m_gameWindow.clear();
    for(auto it = m_tileSprites.begin(); it != m_tileSprites.end(); it++)
    {
        m_gameWindow.draw(*it);
    }
    m_gameWindow.display();
}
