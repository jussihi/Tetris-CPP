/*
 * TetrisGame.hpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#include <cstdint>
#include "TetrisUtils.hpp"

#ifndef TETRISCLASSES_HPP_
#define TETRISCLASSES_HPP_

class TetrisBlock {
public:
    TetrisBlock(blockType w_type);
    ~TetrisBlock();

private:

};

class TetrisGrid {
public:
    TetrisGrid(uint32_t w_rows, uint32_t w_cols);
    virtual
    ~TetrisGrid();

    void clearAll();


    uint32_t m_rows;
    uint32_t m_cols;

};


class TetrisGame {
public:
    TetrisGame ();
    virtual
    ~TetrisGame ();
};

#endif /* TETRISCLASSES_HPP_ */
