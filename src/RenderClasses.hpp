/*
 * RenderClasses.hpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#include "TetrisClasses.hpp"

#ifndef RENDERCLASSES_HPP_
#define RENDERCLASSES_HPP_

class SpriteRenderer {
public:
    SpriteRenderer ();

    virtual
    ~SpriteRenderer();
};

class GridRenderer {
public:
    GridRenderer ();
    virtual
    ~GridRenderer ();

    void renderTiles(const TetrisGrid& w_tetrisBoard);
};

#endif /* RENDERCLASSES_HPP_ */
