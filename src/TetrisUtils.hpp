/*
 * TetrisUtils.hpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#ifndef TETRISUTILS_HPP_
#define TETRISUTILS_HPP_

#include <vector>



enum GameState {
    sStop = 0,  // ?? turhaa?
    sPlay,
    sPause,
    sGameOver,
    sQuit
};

enum BlockType {
    tE = -1,
    tT = 0,
    tZ,
    tJ,
    tO,
    tL,
    tS,
    tI
};

enum BlockColor {
    cEmpty = -1,
    c1 = 0,
    c2,
    c3
};

typedef std::vector<std::vector<bool>> BlockBody;

#endif /* TETRISUTILS_HPP_ */
