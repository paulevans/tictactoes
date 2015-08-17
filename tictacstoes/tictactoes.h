//
//  tictactoes.h
//  tictacstoes
//
//  Created by Paul Evans on 8/16/15.
//  Copyright (c) 2015 Paul Evans. All rights reserved.
//

#ifndef tictacstoes_tictactoes_h
#define tictacstoes_tictactoes_h

// My gamedev brain is bulking at this... but std::string...
#include <string>

uint32_t evaluateTicTacToes(
                            const std::string& input /**< [in] description for game in 9 characters */
                            , std::string& output /**< [out] description of game outcome */
);


#endif
