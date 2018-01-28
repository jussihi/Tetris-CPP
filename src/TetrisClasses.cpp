/*
 * TetrisGame.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#include "TetrisClasses.hpp"


/*
 *  TETRIS BLOCK CLASS FUNCTION
 */
TetrisBlock::TetrisBlock(blockType w_type)
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
            m_body = {{cEmpty, cBlue, cEmpty},
                      {cBlue, cBlue, cBlue},
                      {cEmpty, cEmpty, cEmpty}};
            break;
        }
        case tS:
        {
            m_body = {{cEmpty, cBlue, cBlue},
                      {cBlue, cBlue, cEmpty},
                      {cEmpty, cEmpty, cEmpty}};
            break;
        }
        case tZ:
        {
            m_body = {{cBlue, cBlue, cEmpty},
                      {cEmpty, cBlue, cBlue},
                      {cEmpty, cEmpty, cEmpty}};
            break;
        }
        case tJ:
        {
            m_body = {{cBlue, cEmpty, cEmpty},
                      {cBlue, cBlue, cBlue},
                      {cEmpty, cEmpty, cEmpty}};
            break;
        }
        case tL:
        {
            m_body = {{cEmpty, cEmpty, cBlue},
                      {cBlue, cBlue, cBlue},
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

/*
 *  TETRIS PLAYGRID CLASS FUNCTIONS
 */
TetrisGrid::TetrisGrid(uint32_t w_rows, uint32_t w_cols) : m_rows(w_rows), m_cols(w_cols)
{
    m_tiles.resize(w_cols);
    for(std::vector<BlockColor>& vec : m_tiles)
    {
        vec.resize(w_rows);
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
    m_tiles[w_col][w_row] = w_color;
}

bool TetrisGrid::canBlockFit(uint32_t& w_row, uint32_t& w_col, const TetrisBlock& w_block) const
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


/*
 *  GAME PLACEHOLDER CLASS FUNCTIONS
 */
TetrisGame::TetrisGame (TetrisGrid& w_tetrisGrid, const double& w_tickDelta) : m_tetrisGrid(w_tetrisGrid), m_tickDelta(w_tickDelta)
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

}

