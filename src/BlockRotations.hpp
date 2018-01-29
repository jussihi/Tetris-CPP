/*
 * BlockRotations.hpp
 *
 *  Created on: Jan 29, 2018
 *      Author: jussi
 */

#ifndef BLOCKROTATIONS_HPP_
#define BLOCKROTATIONS_HPP_

#include "TetrisUtils.hpp"



std::vector<BlockBody> blockRotationsI = {
        {{false, false, true, false},
         {false, false, true, false},
         {false, false, true, false},
         {false, false, true, false}},

        {{false, false, false, false},
         {false, false, false, false},
         {true,  true,  true,  true },
         {false, false, false, false}}
};

std::vector<BlockBody> blockRotationsO = {
        {{true, true},
         {true, true}}
};

std::vector<BlockBody> blockRotationsT = {
        {{false, true, false},
         {false, true, true },
         {false, true, false}},

        {{false, true,  false},
         {true,  true,  true },
         {false, false, false}},

        {{false, true, false},
         {true,  true, false},
         {false, true, false}},

        {{false, false, false},
         {true,  true,  true },
         {false, true,  false}}
};

std::vector<BlockBody> blockRotationsS = {
        {{false, false, true},
         {false, true, true },
         {false, true, false}},

        {{false, false, false},
         {true,  true,  false},
         {false, true,  true }},
};

std::vector<BlockBody> blockRotationsZ = {
        {{false, true,  false},
         {false, true,  true },
         {false, false, true}},

        {{false, false, false},
         {false, true,  true },
         {true,  true,  false}}
};

std::vector<BlockBody> blockRotationsJ = {
        {{false, true, false},
         {false, true, false},
         {false, true, true }},

        {{false, false, true },
         {true,  true,  true },
         {false, false, false}},

        {{true,  true, false},
         {false, true, false},
         {false, true, false}},

        {{false, false, false},
         {true,  true,  true },
         {true,  false, false}}
};

std::vector<BlockBody> blockRotationsL = {
        {{false, true, true },
         {false, true, false},
         {false, true, false}},

        {{true,  false, false},
         {true,  true,  true },
         {false, false, false}},

        {{false, true, false},
         {false, true, false},
         {true,  true, false}},

        {{false, false, false},
         {true,  true,  true },
         {false, false, true }}
};


#endif /* BLOCKROTATIONS_HPP_ */
