//
//  tictactoe.cpp
//  tictacstoes
//
//  Created by Paul Evans on 8/16/15.
//  Copyright (c) 2015 Paul Evans. All rights reserved.
//

// Did originally have code all in header
// Then moved it to this cpp file and learned more about xcode's "build phases" ;)
#include "tictactoes.h"

// For cin and cout
#include <iostream>

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

///
/// NOTE: Interesting thing here is that C++ 11 style is to return the value
/// ... rather than use an out param. That's just too far for me! ;)
///
/// @returns encoded game
/// Cannot think of way of encoding game in 8 bits (9 spaces)
/// Cannot think of way of encoding game in 16 bits (9 spaces x 2 players = 18)
/// So may as well encode extra info in 32 bits
/// -- 1st 9 bits [00..08] 0 == empty, 1 == either player taken
/// -- 2nd 9 bits [09..17] 0 == x not at pos, 1 == x is at pos
/// -- 3rd 9 bits [18..26] 0 == o not at pos, 1 == i is at pos
///
/// This gives us a really cheap way to seeing if any moves are left
/// 0X1FF (511) means all positions have been taken.
///
/// Examples:
/// Empty Pos x player  y player
/// 000000000 000000000 000000000
uint32_t evaluateTicTacToes(
                            const std::string& input /**< [in] description for game in 9 characters */
                            , std::string& output /**< [out] description of game outcome */
)
{
    // See if we're playing fair when assertions are active.
    // Using assertions like this are like executable comments about method expectations.
    assert(input.length() == 9);
    
    // C++ 11 has precise numerical types built in! Neat.
    uint8_t boardPosition = 0;
    
    // We are encoding in to an int because bit compares should be way cheaper in a native language
    uint32_t encodedGame = 0;
    
    // trying out fany pants C++ 11 syntax
    // We take one pass only compairing characters to encode our game state
    /// trying out auto rather than const char& (C++ 11)
    for (auto c : input)
    {
        // If statements create branches, switches can create lookup tables (overkill)
        if (c == 'x')
        {
            // Encode board position being taken
            encodedGame |= 1 << boardPosition;
            // Encode player x taking same board position
            encodedGame |= 1 << boardPosition << 9;
        }
        else if (c == 'o')
        {
            // Encode board position being taken
            encodedGame |= 1 << boardPosition;
            // Encode player x taking same board position
            encodedGame |= 1 << boardPosition << 18;
        }
        else
        {
            // No encoding to do.
            // Right now we don't warn of invalid data, but in debug we might want to know
            // So again, assert to document expectation.
            assert(c == '-');
        }
        
        // pre-increment skips an evaluation that post could have
        ++boardPosition;
    }
    
    // If this were a bigger grid I would use a for loop or something to figure
    // out flags. But the problem space is limited so why complicate it.
    // Anyway I want to see how constexpr works ;)
    // Keeping to 32 bit uints so no casting required etc.
    constexpr uint32_t X_WIN_HOR_TOP = 0xE00;
    constexpr uint32_t X_WIN_HOR_MIDDLE = 0xE00 << 3;
    constexpr uint32_t X_WIN_HOR_BOTTOM = 0xE00 << 6;
    constexpr uint32_t O_WIN_HOR_TOP = 0xE00 << 9;
    constexpr uint32_t O_WIN_HOR_MIDDLE = 0xE00 << 12;
    constexpr uint32_t O_WIN_HOR_BOTTOM = 0xE00 << 15;
    
    // Now there are two types of diagonals that should be just shifts
    constexpr uint32_t X_WIN_DIAG_LEFT = 0x22200;
    // 0xA800 derived from test case 0x1500000 shifted 9 times to right
    constexpr uint32_t X_WIN_DIAG_RIGHT = 0xA800;
    constexpr uint32_t O_WIN_DIAG_LEFT = X_WIN_DIAG_LEFT << 9;
    constexpr uint32_t O_WIN_DIAG_RIGHT = X_WIN_DIAG_RIGHT << 9;
    
    constexpr uint32_t X_WIN_VERT_LEFT = 0x9200;
    constexpr uint32_t X_WIN_VERT_MIDDLE = 0x9200 << 1;
    constexpr uint32_t X_WIN_VERT_RIGHT = 0x9200 << 2;
    constexpr uint32_t O_WIN_VERT_LEFT = 0x9200 << 9;
    constexpr uint32_t O_WIN_VERT_MIDDLE = 0x9200 << 10;
    constexpr uint32_t O_WIN_VERT_RIGHT = 0x9200 << 11;
    
    // Yoda if I guess. Old habits and all that
    if (X_WIN_HOR_TOP == (X_WIN_HOR_TOP & encodedGame)
        || X_WIN_HOR_MIDDLE == (X_WIN_HOR_MIDDLE & encodedGame)
        || X_WIN_HOR_BOTTOM == (X_WIN_HOR_BOTTOM & encodedGame)
        || X_WIN_DIAG_LEFT == (X_WIN_DIAG_LEFT & encodedGame)
        || X_WIN_DIAG_RIGHT == (X_WIN_DIAG_RIGHT & encodedGame)
        || X_WIN_VERT_LEFT == (X_WIN_VERT_LEFT & encodedGame)
        || X_WIN_VERT_MIDDLE == (X_WIN_VERT_MIDDLE & encodedGame)
        || X_WIN_VERT_RIGHT == (X_WIN_VERT_RIGHT & encodedGame)
        )
    {
        output = "X wins";
    }
    else if (O_WIN_HOR_TOP == (O_WIN_HOR_TOP & encodedGame)
             || O_WIN_HOR_MIDDLE == (O_WIN_HOR_MIDDLE & encodedGame)
             || O_WIN_HOR_BOTTOM == (O_WIN_HOR_BOTTOM & encodedGame)
             || O_WIN_DIAG_LEFT == (O_WIN_DIAG_LEFT & encodedGame)
             || O_WIN_DIAG_RIGHT == (O_WIN_DIAG_RIGHT & encodedGame)
             || O_WIN_VERT_LEFT == (O_WIN_VERT_LEFT & encodedGame)
             || O_WIN_VERT_MIDDLE == (O_WIN_VERT_MIDDLE & encodedGame)
             || O_WIN_VERT_RIGHT == (O_WIN_VERT_RIGHT & encodedGame)
             )
    {
        output = "O wins";
    }
    // 0X1FF == first 9 bits set (so all positions gone)
    // Testing after win checks as last move could have been winner
    else if (0X1FF == (0X1FF & encodedGame))
    {
        output = "Tie Game";
    }
    else
    {
        output = "In Progress";
    }
    
    return encodedGame;
}