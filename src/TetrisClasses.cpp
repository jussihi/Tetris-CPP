/*
 * TetrisGame.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#include "TetrisClasses.hpp"
#include "BlockRotations.hpp"
#include <iostream>

/*
 *  TETRIS BLOCK CLASS FUNCTION
 */
TetrisBlock::TetrisBlock(const BlockType w_type) : m_blockType(w_type), m_blockColor(cBlue), m_currRotation(0)
{
    // ugly hard coded way to
    // store the block body

    // maybe add all possible rotations and just cycle between them
    // with the vector
    g_maxRotations = 0;
    switch(w_type)
    {
        case tI:
        {
            m_body = blockRotationsI;
            break;
        }
        case tO:
        {
            m_body = blockRotationsO;
            break;
        }
        case tT:
        {
            m_body = blockRotationsT;
            break;
        }
        case tS:
        {
            m_body = blockRotationsS;
            break;
        }
        case tZ:
        {
            m_body = blockRotationsZ;
            break;
        }
        case tJ:
        {
            m_body = blockRotationsJ;
            break;
        }
        case tL:
        {
            m_body = blockRotationsL;
            break;
        }
        default:
        {
            break;
        }
    }
    g_maxRotations = m_body.size();
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
TetrisGrid::TetrisGrid(uint32_t w_rows, uint32_t w_cols) : m_rows(w_rows), m_cols(w_cols), m_currBlockRow(0), m_currBlockCol(0), m_currBlock(tI), m_nextBlock(tI), m_score(0), m_level(1)
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

BlockColor TetrisGrid::getTileColor(const uint32_t& w_row, const uint32_t& w_col) const
{
    return m_tiles[w_col][w_row];
}

bool TetrisGrid::canBlockFit(const uint32_t& w_row, const uint32_t& w_col, const TetrisBlock& w_block) const
{
    uint32_t rowCheck, colCheck;
    BlockBody blockBody = w_block.getBody();
    for(uint32_t blockCol = 0; blockCol < blockBody.size(); blockCol++)
    {
        for(uint32_t blockRow = 0; blockRow < blockBody[0].size(); blockRow++)
        {
            rowCheck = w_row + blockRow;
            colCheck = w_col + blockCol;
            if(isOccupied(rowCheck, colCheck) && blockBody[blockCol][blockRow] != false)
            {
                return false;
            }
        }
    }
    return true;
}

bool TetrisGrid::isOccupied(uint32_t& w_row, uint32_t& w_col) const
{
    if(w_row < 0 || w_row >= m_rows || w_col < 0 || w_col >= m_cols || m_tiles[w_col][w_row] != cEmpty)
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
    m_nextBlock = TetrisBlock(static_cast<BlockType>(rand()%6 + 1));

    m_currBlockRow = 0; // TODO: change this to negative value

    m_currBlockCol = (m_cols - m_currBlock.getBody().size()) / 2;

    return true;        // TODO : Add check if not possible to add
}

bool TetrisGrid::isBlockAtBottom() const
{
    return !canBlockFit(m_currBlockRow + 1, m_currBlockCol, m_currBlock);
}

bool TetrisGrid::freezeCurrentBlockToGrid() // TODO: return false
{
    uint32_t currRow, currCol;
    BlockBody blockBody = m_currBlock.getBody();
    for(uint32_t blockCol = 0; blockCol < blockBody.size(); blockCol++)
    {
        for(uint32_t blockRow = 0; blockRow <blockBody[0].size(); blockRow++)
        {
            currRow = m_currBlockRow + blockRow;
            currCol = m_currBlockCol + blockCol;
            if(blockBody[blockCol][blockRow] != false)
            {
                setTileColor( m_currBlock.getColor(), currRow, currCol);
            }
        }
    }

    // call some function to check if lines need to be cleared

    spawnBlock();
    return true;
}

const std::vector<std::vector<BlockColor>>& TetrisGrid::getTiles() const
{
    return m_tiles;
}

void TetrisGrid::tryMoveRotateCurrentBlock(const int32_t& w_movementHorizontal, const int32_t& w_rotation)
{
    if(w_movementHorizontal)
    {
        if( w_movementHorizontal < 0)
        {
            for(int i = w_movementHorizontal; i < 0; i++)
            {
                if(canBlockFit(m_currBlockRow, m_currBlockCol - 1, m_currBlock))
                {
                    m_currBlockCol--;
                }
                else break;
            }
        }
        else
        {
            for(int i = 0; i < w_movementHorizontal; i++)
            {
                if(canBlockFit(m_currBlockRow, m_currBlockCol + 1, m_currBlock))
                {
                    m_currBlockCol++;
                }
                else break;
            }
        }
    }
    if(w_rotation)
    {
        TetrisBlock rotateBlock = m_currBlock;
        uint8_t newRotation;
        if(w_rotation < 0)
        {
            // counter clockwise

            for(int i = w_rotation; i < 0; i++)
            {
                if(m_currBlock.getRotation() == 0)
                {
                    newRotation = m_currBlock.g_maxRotations - 1;

                }
                else
                {
                    newRotation = m_currBlock.getRotation() - 1;
                }

                rotateBlock.setRotation(newRotation);

                if(canBlockFit(m_currBlockRow, m_currBlockCol, rotateBlock))
                {
                    m_currBlock.setRotation(newRotation);
                }
                else break;
            }
        }
        else
        {
            // clockwise
            for(int i = 0; i < w_movementHorizontal; i++)
            {
                if(m_currBlock.getRotation() == m_currBlock.g_maxRotations - 1)
                {
                    newRotation = 0;

                }
                else
                {
                    newRotation = m_currBlock.getRotation() + 1;
                }

                rotateBlock.setRotation(newRotation);

                if(canBlockFit(m_currBlockRow, m_currBlockCol, rotateBlock))
                {
                    m_currBlock.setRotation(newRotation);
                }
                else break;
            }
        }
    }
}

void TetrisGrid::removeFullRows()
{
    uint8_t rowsRemoved = 0;

    for(uint32_t row = 0; row < m_rows; row++)
    {
        for(uint32_t col = 0; col < m_cols; col++)
        {
            if(m_tiles[col][row] == cEmpty)
                break;

            if(col == m_cols -1)
            {
                rowsRemoved++;
                for(uint32_t col = 0; col < m_cols; col++)
                {
                    m_tiles[col].erase(m_tiles[col].begin() + row);
                    m_tiles[col].insert(m_tiles[col].begin(), cEmpty);
                }
            }
        }
    }
    // calculate score
    // tetris.wikia.com/wiki/Scoring
    // store amount of soft drops somewhere!
    switch (rowsRemoved)
    {
        case 1:
            m_score += 40 * (m_level + 1);
            break;
        case 2:
            m_score += 100 * (m_level + 1);
            break;
        case 3:
            m_score += 300 * (m_level + 1);
            break;
        case 4:
            m_score += 1200 * (m_level + 1);
            break;
    }

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
void TetrisGame::tick(const int32_t& w_movementHorizontal, const int32_t& w_rotation)
{
    m_moveDownTimer += m_tickDelta;

    if(w_movementHorizontal || w_rotation)
    {
        m_tetrisGrid.tryMoveRotateCurrentBlock(w_movementHorizontal, w_rotation);
    }

    if(m_tetrisGrid.isBlockAtBottom())
    {
        if(m_moveDownTimer >= m_moveDownDelta)
        {
            m_tetrisGrid.freezeCurrentBlockToGrid();
            m_tetrisGrid.removeFullRows();
            m_moveDownTimer = 0.0;
        }
    }
    else if(m_moveDownTimer >= m_moveDownDelta)
    {
        // TODO: do correction of the overflow time
        // also do it elsewhere too...
        m_tetrisGrid.moveDown();
        m_moveDownTimer = 0.0;
    }


}

void TetrisGame::newBlock()
{
    m_tetrisGrid.spawnBlock();
}
