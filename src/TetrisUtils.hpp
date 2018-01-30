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
    tE = 0,
    tI,
    tO,
    tT,
    tS,
    tZ,
    tJ,
    tL
};

enum BlockColor {
    cEmpty = 0,
    cBlue,
    cRed,
    cLBlue,
    cCyan,
    cGreen,
    cPink
};

typedef std::vector<std::vector<bool>> BlockBody;

#endif /* TETRISUTILS_HPP_ */
