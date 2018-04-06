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
#include <iomanip>

#define FONTSIZE 32


RenderClass::RenderClass(TetrisGrid& w_tetrisGrid, sf::RenderWindow& w_gameWindow, const uint32_t& w_offsetX, const uint32_t& w_offsetY, const bool& multiPlayer) : m_tetrisGrid(w_tetrisGrid), m_gameWindow(w_gameWindow), m_offsetX(w_offsetX), m_offsetY(w_offsetY)
{
    std::stringstream ss;

    m_tileTextures.resize(10);
    for(uint32_t i = 0; i < 10; i++)
    {
        m_tileTextures[i].resize(3);
        for(uint32_t j = 0; j < 3; j++)
        {
            ss << "../textures/blocks/" << i << "-" << j << ".png";
            m_tileTextures[i][j].loadFromFile(ss.str());
            ss.clear();
            ss.str(std::string());
        }
    }

    m_font.loadFromFile("../textures/NESFont.ttf");

    m_texBG.loadFromFile("../textures/tetrisBG.png");

    m_spriteBG = sf::Sprite(m_texBG);



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

    ss << "LEVEL\n  " << std::setfill('0') << std::setw(2) << w_tetrisGrid.getLevel();
    m_levelText.setFont(m_font);
    m_levelText.setString(ss.str());
    m_levelText.setCharacterSize(FONTSIZE);
    m_levelText.setPosition(sf::Vector2f(m_offsetX + 385, m_offsetY + 440 ));
}


RenderClass::~RenderClass()
{

}

void RenderClass::updateGraphics()
{
    m_tileSprites.clear();

    m_level = m_tetrisGrid.getLevel();

    for(uint32_t col = 0; col < m_tetrisGrid.getCols(); col++)
    {
        for(uint32_t row = 0; row < m_tetrisGrid.getRows(); row++)
        {
            BlockColor currColor = m_tetrisGrid.getTileColor(row, col);
            if(currColor != cEmpty)
            {
                sf::Sprite sprite;
                sprite.setTexture(m_tileTextures[m_level][currColor]);
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
            if(currBody[blockCol][blockRow] != false)
            {
                sf::Sprite sprite;
                sprite.setTexture(m_tileTextures[m_level][currColor]);
                sprite.setPosition(sf::Vector2f(m_offsetX + 32 * (blockCol + m_tetrisGrid.getCurrBlockCol()), m_offsetY +  32 * (blockRow + m_tetrisGrid.getCurrBlockRow())));
                m_tileSprites.push_back(sprite);
            }
        }
    }

    BlockBody nextBody = m_tetrisGrid.getNextBlock().getBody();
    BlockColor nextColor = m_tetrisGrid.getNextBlock().getColor();
    BlockType nextType = m_tetrisGrid.getNextBlock().getType();

    for(uint32_t blockCol = 0; blockCol < nextBody[0].size(); blockCol++)
    {
        for(uint32_t blockRow = 0; blockRow < nextBody.size(); blockRow++)
        {
            if(nextBody[blockCol][blockRow] != false)
            {
                sf::Sprite sprite;
                sprite.setTexture(m_tileTextures[m_level][nextColor]);
                switch (nextType)
                {
                    case tI:
                        sprite.setPosition(sf::Vector2f(m_offsetX + 385 + (32 * blockCol), m_offsetY + 240 + (32 * blockRow)));
                        break;
                    case tJ:
                    case tL:
                    case tT:
                    case tS:
                    case tZ:
                        sprite.setPosition(sf::Vector2f(m_offsetX + 385 + 16 + (32 * blockCol), m_offsetY + 240 + 16 + (32 * blockRow)));
                        break;
                    default:
                        sprite.setPosition(sf::Vector2f(m_offsetX + 385 + 32 + (32 * blockCol), m_offsetY + 240 + 32 + (32 * blockRow)));
                        break;
                }
                m_tileSprites.push_back(sprite);
            }
        }
    }

    // text boxes

    std::stringstream ss;

    ss << " TOP\n " << std::setfill('0') << std::setw(6) << "10000" << "\n\n SCORE\n " << std::setfill('0') << std::setw(6) <<  m_tetrisGrid.getScore();
    m_score.setString(ss.str());

    ss.clear();
    ss.str(std::string());

    ss << "LINES-" << std::setfill('0') << std::setw(3) << m_tetrisGrid.getClearedRows();
    m_lines.setString(ss.str());

    ss.clear();
    ss.str(std::string());

    ss << "LEVEL\n  " << std::setfill('0') << std::setw(2) << m_level;
    m_levelText.setString(ss.str());

    // update screen
    m_gameWindow.clear();
    m_gameWindow.draw(m_spriteBG);
    m_gameWindow.draw(m_score);
    m_gameWindow.draw(m_lines);
    m_gameWindow.draw(m_nextText);
    m_gameWindow.draw(m_levelText);
    for(auto it = m_tileSprites.begin(); it != m_tileSprites.end(); it++)
    {
        m_gameWindow.draw(*it);
    }
    m_gameWindow.display();
}
