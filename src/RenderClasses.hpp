/*
 * RenderClasses.hpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#include "TetrisClasses.hpp"
#include "graphics.hpp"

#ifndef RENDERCLASSES_HPP_
#define RENDERCLASSES_HPP_

class RenderClass {
public:
    RenderClass(TetrisGrid& w_tetrisGrid, sf::RenderWindow& w_gameWindow, const uint32_t& w_offsetX, const uint32_t& w_offsetY, const bool& multiPlayer);

    virtual
    ~RenderClass();

    void updateGraphics();

private:
    TetrisGrid& m_tetrisGrid;
    sf::RenderWindow& m_gameWindow;
    std::vector<std::vector<sf::Texture>> m_tileTextures;
    std::vector<sf::Sprite> m_tileSprites;
    sf::Font m_font;

    uint32_t m_level;

    sf::Texture m_texBG;
    sf::Sprite m_spriteBG;

    uint32_t m_offsetX;
    uint32_t m_offsetY;


    /*
     * Text boxes
     */
    sf::Text m_score;
    sf::Text m_scoreDiff;
    sf::Text m_lines;
    sf::Text m_playerText;
    sf::Text m_nextText;
    sf::Text m_levelText;
};

#endif /* RENDERCLASSES_HPP_ */
