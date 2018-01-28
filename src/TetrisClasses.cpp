/*
 * TetrisGame.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#include "TetrisClasses.hpp"
#include <iostream>

/*
 *  TETRIS BLOCK CLASS FUNCTION
 */
TetrisBlock::TetrisBlock(const BlockType w_type) : m_blockType(w_type), m_blockColor(cBlue)
{
    // ugly hard coded way to
    // store the block body

    // maybe add all possible rotations and just cycle between them
    // with the vector
    switch(w_type)
    {
        case tI:
        {
            m_body = {{cEmpty, cEmpty, cBlue, cEmpty},
                      {cEmpty, cEmpty, cBlue, cEmpty},
                      {cEmpty, cEmpty, cBlue, cEmpty},
                      {cEmpty, cEmpty, cBlue, cEmpty}};
            break;
        }
        case tO:
        {
            m_body = {{cBlue, cBlue},
                      {cBlue, cBlue}};
            break;
        }
        case tT:
        {
            m_body = {{cEmpty, cBlue,  cEmpty},
                      {cBlue,  cBlue,  cBlue },
                      {cEmpty, cEmpty, cEmpty}};
            break;
        }
        case tS:
        {
            m_body = {{cEmpty, cBlue,  cBlue },
                      {cBlue,  cBlue,  cEmpty},
                      {cEmpty, cEmpty, cEmpty}};
            break;
        }
        case tZ:
        {
            m_body = {{cBlue,  cBlue,  cEmpty},
                      {cEmpty, cBlue,  cBlue },
                      {cEmpty, cEmpty, cEmpty}};
            break;
        }
        case tJ:
        {
            m_body = {{cBlue,  cEmpty, cEmpty},
                      {cBlue,  cBlue,  cBlue },
                      {cEmpty, cEmpty, cEmpty}};
            break;
        }
        case tL:
        {
            m_body = {{cEmpty, cEmpty, cBlue },
                      {cBlue,  cBlue,  cBlue },
                      {cEmpty, cEmpty, cEmpty}};
            break;
        }
        default:
        {
            break;
        }
    }
}

TetrisBlock::~TetrisBlock()
{

}

const BlockType& TetrisBlock::getType() const
{
    return m_blockType;
}

BlockColor TetrisBlock::getColor() const
{
    return m_blockColor;
}

/*
 *  TETRIS PLAYGRID CLASS FUNCTIONS
 */
TetrisGrid::TetrisGrid(uint32_t w_rows, uint32_t w_cols) : m_rows(w_rows), m_cols(w_cols), m_currBlockRow(0), m_currBlockCol(0), m_currBlock(tI), m_nextBlock(tI)
{
    m_tiles.resize(w_rows);
    for(std::vector<BlockColor>& vec : m_tiles)
    {
        vec.resize(w_cols);
    }
}

TetrisGrid::~TetrisGrid()
{
    clearAll();
}

void TetrisGrid::clearAll()
{
    for(std::vector<BlockColor>& vec : m_tiles)
    {
        std::fill(vec.begin(), vec.end(), cEmpty);
    }
}

void TetrisGrid::setTileColor(const BlockColor& w_color, const uint32_t& w_row, const uint32_t& w_col)
{
    m_tiles[w_row][w_col] = w_color;
}

BlockColor TetrisGrid::getTileColor(const uint32_t& w_row, const uint32_t& w_col) const
{
    return m_tiles[w_row][w_col];
}

bool TetrisGrid::canBlockFit(const uint32_t& w_row, const uint32_t& w_col, const TetrisBlock& w_block) const
{
    uint32_t rowCheck, colCheck;
    for(uint32_t blockRow = 0; blockRow < w_block.m_body.size(); blockRow++)
    {
        for(uint32_t blockCol = 0; blockCol < w_block.m_body[0].size(); blockCol++)
        {
            rowCheck = w_row + blockRow;
            colCheck = w_col + blockCol;
            if(isOccupied(rowCheck, colCheck) && w_block.m_body[blockRow][blockCol] != cEmpty)
            {
                return false;
            }
        }
    }
    return true;
}

bool TetrisGrid::isOccupied(uint32_t& w_row, uint32_t& w_col) const
{
    if(w_row < 0 || w_row >= m_rows || w_col < 0 || w_col >= m_cols || m_tiles[w_row][w_col] != cEmpty)
    {
        return true;
    }
    return false;
}

void TetrisGrid::moveDown()
{
    if(canBlockFit(m_currBlockRow + 1, m_currBlockCol, m_currBlock))
    {
        m_currBlockRow++;
    }

}

bool TetrisGrid::spawnBlock()
{
    m_currBlock = TetrisBlock(m_nextBlock.getType());

    m_currBlockRow = 0; // TODO: change this to negative value
    m_currBlockCol = (m_cols - m_currBlock.m_body[0].size()) / 2;

    return true;        // TODO : Add check if not possible to add
}

bool TetrisGrid::isBlockAtBottom() const
{
    return !canBlockFit(m_currBlockRow + 1, m_currBlockCol, m_currBlock);
}

bool TetrisGrid::freezeCurrentBlockToGrid() // TODO: return false
{
    uint32_t currRow, currCol;

    for(uint32_t blockRow = 0; blockRow < m_currBlock.m_body.size(); blockRow++)
    {
        for(uint32_t blockCol = 0; blockCol < m_currBlock.m_body[0].size(); blockCol++)
        {
            currRow = m_currBlockRow + blockRow;
            currCol = m_currBlockCol + blockCol;
            setTileColor( m_currBlock.getColor(), currRow, currCol);
        }
    }

    // call some function to check if lines need to be cleared
    return true;
}

const std::vector<std::vector<BlockColor>>& TetrisGrid::getTiles() const
{
    return m_tiles;
}


/*
 *  GAME PLACEHOLDER CLASS FUNCTIONS
 */
TetrisGame::TetrisGame (TetrisGrid& w_tetrisGrid, const double& w_tickDelta) : m_tetrisGrid(w_tetrisGrid), m_tickDelta(w_tickDelta), m_moveDownDelta(0.8), m_moveDownTimer(0.0)
{

}

TetrisGame::~TetrisGame ()
{
    // TODO Auto-generated destructor stub
}

// process one tick in game time
// ( one tick every 1 / FPS second)
void TetrisGame::tick()
{
    m_moveDownTimer += m_tickDelta;

    if(m_moveDownTimer >= m_moveDownDelta)
    {
        // TODO: do correction of the overflow time
        // also do it elsewhere too...
        m_tetrisGrid.moveDown();
        m_moveDownTimer = 0.0;
    }

    if(m_tetrisGrid.isBlockAtBottom())
    {
        // TODO: joku odotusaika tähän
        // if(odotusaika..)
        m_tetrisGrid.freezeCurrentBlockToGrid();
    }
}

void TetrisGame::newBlock()
{
    m_tetrisGrid.spawnBlock();
}
