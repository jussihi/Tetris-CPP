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

    BlockColor getColor() const;

    BlockBody getBody() const { return m_body[m_currRotation]; }

    uint8_t g_maxRotations;

    const uint8_t getRotation() const { return m_currRotation; }

    void setRotation(uint8_t w_rotation) { m_currRotation = w_rotation; }

private:
    std::vector<BlockBody> m_body;
    BlockType m_blockType;
    BlockColor m_blockColor;
    uint8_t m_currRotation;
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

    const std::vector<std::vector<BlockColor>>& getTiles() const;

    BlockColor getTileColor(const uint32_t& w_row, const uint32_t& w_col) const;

    uint32_t getRows() const { return m_rows; }
    uint32_t getCols() const { return m_cols; }

    TetrisBlock getCurrBlock() const { return m_currBlock; }

    uint32_t getCurrBlockRow() { return m_currBlockRow; }
    uint32_t getCurrBlockCol() { return m_currBlockCol; }

    void tryMoveRotateCurrentBlock(const int32_t& w_movementHorizontal, const int32_t& w_rotation);

    void removeFullRows();

    void checkLevelAdvance();

    uint32_t getScore() const { return m_score; }

    uint32_t getLevel() const { return m_level; }

    void tickGrid(const bool& w_softDrop);

    uint32_t getClearedRows() const { return m_rowsCleared; }


private:

    bool isOccupied(uint32_t& w_row, uint32_t& w_col) const;

    void setTileColor(const BlockColor& w_color, const uint32_t& w_row, const uint32_t& w_col);

    uint32_t m_rows;
    uint32_t m_cols;

    std::vector<std::vector<BlockColor>> m_tiles;

    int32_t m_currBlockRow;
    uint32_t m_currBlockCol;

    TetrisBlock m_currBlock;
    TetrisBlock m_nextBlock;

    uint32_t m_score;
    uint32_t m_level;
    uint32_t m_startLevel;
    uint32_t m_rowsCleared;
    uint32_t m_levelRowsCleared;

    std::vector<uint32_t> m_levelG;

    uint32_t m_moveDownTick;
};


class TetrisGame {
public:
    TetrisGame (TetrisGrid& w_tetrisGrid, const double& w_tickDelta);
    virtual
    ~TetrisGame ();

    void tick(const int32_t& w_movementHorizontal, const int32_t& w_rotation, const bool& w_softDrop);

    void newBlock();

private:
    TetrisGrid& m_tetrisGrid;
    double m_tickDelta;
    double m_moveDownDelta;

    // timers
    double m_moveDownTimer;
};

#endif /* TETRISCLASSES_HPP_ */
