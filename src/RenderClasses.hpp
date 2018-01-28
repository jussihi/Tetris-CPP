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
    RenderClass(TetrisGrid& w_tetrisGrid, sf::RenderWindow& w_gameWindow);

    virtual
    ~RenderClass();

    void updateGraphics();

private:
    TetrisGrid& m_tetrisGrid;
    sf::RenderWindow& m_gameWindow;
    std::vector<sf::Texture> m_tileTextures;
    std::vector<sf::Sprite> m_tileSprites;
};

#endif /* RENDERCLASSES_HPP_ */
