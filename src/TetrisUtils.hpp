/*
 * TetrisUtils.hpp
 *
 *  Created on: Jan 28, 2018
 *      Author: jussi
 */

#ifndef TETRISUTILS_HPP_
#define TETRISUTILS_HPP_

enum GameState {
    sStop = 0,  // ?? turhaa?
    sPlay,
    sPause,
    sGameOver,
    sQuit
};

enum blockType {
    tI = 1,
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



#endif /* TETRISUTILS_HPP_ */
