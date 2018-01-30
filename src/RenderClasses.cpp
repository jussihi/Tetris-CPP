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
#include <string>
#include <sstream>

#define FONTSIZE 32


RenderClass::RenderClass(TetrisGrid& w_tetrisGrid, sf::RenderWindow& w_gameWindow, const uint32_t& w_offsetX, const uint32_t& w_offsetY, const bool& multiPlayer) : m_tetrisGrid(w_tetrisGrid), m_gameWindow(w_gameWindow), m_offsetX(w_offsetX), m_offsetY(w_offsetY)
{
    m_tileTextures.resize(7);
    m_tileTextures[1].loadFromFile("../textures/blue.png");
    m_tileTextures[2].loadFromFile("../textures/red.png");
    m_tileTextures[3].loadFromFile("../textures/lblue.png");
    m_tileTextures[4].loadFromFile("../textures/cyan.png");
    m_tileTextures[5].loadFromFile("../textures/green.png");
    m_tileTextures[6].loadFromFile("../textures/pink.png");

    m_font.loadFromFile("../textures/NESFont.ttf");

    m_texBG.loadFromFile("../textures/tetrisBG.png");

    m_spriteBG = sf::Sprite(m_texBG);

    std::stringstream ss;

    // text boxes
    // MAKE SINGLE PLAYER VARIANTS

    ss << " TOP\n10000\n\n SCORE\n " << m_tetrisGrid.getScore();
    m_score.setFont(m_font);
    m_score.setString(ss.str());
    m_score.setCharacterSize(FONTSIZE - 2);
    m_score.setPosition(sf::Vector2f(m_offsetX + 375, m_offsetY -  80 ));

    ss.clear();
    ss.str(std::string());

    ss << "LINES-000"; // << 000;
    m_lines.setFont(m_font);
    m_lines.setString(ss.str());
    m_lines.setCharacterSize(FONTSIZE);
    m_lines.setPosition(sf::Vector2f(m_offsetX + 36, m_offsetY - 100 ));

    ss.clear();
    ss.str(std::string());

    ss << "NEXT";
    m_nextText.setFont(m_font);
    m_nextText.setString(ss.str());
    m_nextText.setCharacterSize(FONTSIZE);
    m_nextText.setPosition(sf::Vector2f(m_offsetX + 385, m_offsetY + 221 ));

    ss.clear();
    ss.str(std::string());

    ss << "LEVEL\n  00";
    m_level.setFont(m_font);
    m_level.setString(ss.str());
    m_level.setCharacterSize(FONTSIZE);
    m_level.setPosition(sf::Vector2f(m_offsetX + 385, m_offsetY + 440 ));
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
                sprite.setPosition(sf::Vector2f(m_offsetX + 32 * col, m_offsetY +  32 * row));
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
                sprite.setPosition(sf::Vector2f(m_offsetX + 32 * (blockCol + m_tetrisGrid.getCurrBlockCol()), m_offsetY +  32 * (blockRow + m_tetrisGrid.getCurrBlockRow())));
                m_tileSprites.push_back(sprite);
            }
        }
    }

    /*
    // text boxes
    sf::Text score;
    score.setFont(m_font);
    std::stringstream a;
    a << " SCORE\n" << m_tetrisGrid.getScore();
    score.setString(a.str());
    score.setCharacterSize(30);
    score.setPosition(sf::Vector2f(m_offsetX + 390, m_offsetY +  32 ));
*/

    // update screen
    m_gameWindow.clear();
    m_gameWindow.draw(m_spriteBG);
    m_gameWindow.draw(m_score);
    m_gameWindow.draw(m_lines);
    m_gameWindow.draw(m_nextText);
    m_gameWindow.draw(m_level);
    for(auto it = m_tileSprites.begin(); it != m_tileSprites.end(); it++)
    {
        m_gameWindow.draw(*it);
    }
    m_gameWindow.display();
}
