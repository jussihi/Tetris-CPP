/*
 * TetrisGame.hpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#include <cstdint>
#include <vector>
#include "TetrisUtils.hpp"

#ifndef TETRISCLASSES_HPP_
#define TETRISCLASSES_HPP_

class TetrisBlock {
public:
    TetrisBlock(const BlockType w_type);
    ~TetrisBlock();

    const BlockType& getType() const;

    std::vector<std::vector<BlockColor>> m_body;

    BlockColor getColor() const;

private:
    BlockType m_blockType;
    BlockColor m_blockColor;

};

class TetrisGrid {
public:
    TetrisGrid(uint32_t w_rows, uint32_t w_cols);
    virtual
    ~TetrisGrid();

    void clearAll();

    // can put into private?
    bool canBlockFit(const uint32_t& w_row, const uint32_t& w_col, const TetrisBlock& w_block) const;

    void moveDown();

    bool spawnBlock();

    bool isBlockAtBottom() const;

    bool freezeCurrentBlockToGrid();

private:

    bool isOccupied(uint32_t& w_row, uint32_t& w_col) const;

    void setTileColor(const BlockColor& w_color, const uint32_t& w_row, const uint32_t& w_col);

    uint32_t m_rows;
    uint32_t m_cols;

    std::vector<std::vector<BlockColor>> m_tiles;

    uint32_t m_currBlockRow;
    uint32_t m_currBlockCol;

    TetrisBlock m_currBlock;
    TetrisBlock m_nextBlock;
};


class TetrisGame {
public:
    TetrisGame (TetrisGrid& w_tetrisGrid, const double& w_tickDelta);
    virtual
    ~TetrisGame ();

    void tick();

    void newBlock();

private:
    TetrisGrid& m_tetrisGrid;
    double m_tickDelta;
    double m_moveDownDelta;

    // timers
    double m_moveDownTimer;
};

#endif /* TETRISCLASSES_HPP_ */
