//
//  main.cpp
//  tests using google test framework
//
//  Created by Paul Evans on 8/16/15.
//  Copyright (c) 2015 Paul Evans. All rights reserved.
//

#include "gtest/gtest.h"
#include "tictactoes.h"

// Normally I would organise things alpabetically.
// But as I am doing test driven I thought it would be fun to show you the order
// I did tests in.

// I followed the create test, fail, pass method of creating tests.
// The first tests are all based on the table at:
// http://supernova-at.github.io/candy/candygrams/tic_tacs_toe.html

// Picked completely empty example first as was most trivial to make pass
TEST (SampleInProgress, Empty)
{
    std::string result;

    EXPECT_EQ(0, evaluateTicTacToes("---------", result));
    
    // At this stage totally cheating and just returning "In Progress" constantly
    EXPECT_EQ("In Progress", result);
}

// Next up in progress but moves had been made.
// This allowed me to check the encoding of the game but still always say "In Progress"
TEST (SampleInProgress, InProgress)
{
    std::string result;
    
    // Copy and pasted this in to calculator to make sure bits set correctly
    // Trick here is reading from right to left.
    EXPECT_EQ(84478919, evaluateTicTacToes("xox---oxo", result));
    
    // Still cheating with "In Progress"
    EXPECT_EQ("In Progress", result);
}

// Bah, actually have to do the testing of game state now ;)
// No more cheating with "In Progress" all the things either.
TEST (SampleXWins, Case1)
{
    std::string result;
    
    // Copy and pasted this in to calculator to make sure bits set correctly
    // Trick here is reading from right to left.
    EXPECT_EQ(88084311, evaluateTicTacToes("xxx-o-o-o", result));
    EXPECT_EQ("X wins", result);
    
    /*
     still cheating... added this to the end to get all the tests passing ;)
     
     // Yoda if I guess. Old habits and all that
     if (0xE00 == (0XE00 & encodedGame))
     {
        output = "X wins";
     }
     else
     {
        output = "In Progress";
     }
     */
}

// Left to right diagonal win for x
TEST (SampleXWins, Case2)
{
    std::string result;
    
    // Copy and pasted this in to calculator to make sure bits set correctly
    // Trick here is reading from right to left.
    EXPECT_EQ(19538779, evaluateTicTacToes("xo-ox-o-x", result));
    EXPECT_EQ("X wins", result);
    
    // Staying with the ttd of doing the simple thing just to pass...
    /*
     // Yoda if I guess. Old habits and all that
     if (0xE00 == (0XE00 & encodedGame) || 0x22200 == (0x22200 & encodedGame))
     {
        output = "X wins";
     }
     else
     {
        output = "In Progress";
     }
     */
}

// Right to left diagonal win for o
// Nice test cases by the way Andy. Def leading me in a nice way.
TEST (SampleYWins, Case1)
{
    std::string result;
    
    // Copy and pasted this in to calculator to make sure bits set correctly
    // Trick here is reading from right to left.
    EXPECT_EQ(22217685, evaluateTicTacToes("x-o-o-oxx", result));
    EXPECT_EQ("O wins", result);
    
    // added to pass:
    /*
     else if (0x1500000 == (0x1500000 & encodedGame))
     {
        output = "O wins";
     }
     */
}

// Right to left diagonal win for o
// Another horizontal win, this time along the middle.
// Starting to suspect the test cases left out verticals on purpose Andy ;)
TEST (SampleYWins, Case2)
{
    std::string result;
    
    // Copy and pasted this in to calculator to make sure bits set correctly
    // Trick here is reading from right to left.
    EXPECT_EQ(14748349, evaluateTicTacToes("x-xooo-x-", result));
    EXPECT_EQ("O wins", result);
    
    // Game eval block now looks like:
    /* 
     // Yoda if I guess. Old habits and all that
     if (0xE00 == (0XE00 & encodedGame) // Top horizontal
        || 0x22200 == (0x22200 & encodedGame)) // Diagonal left to right
     {
        output = "X wins";
     }
     else if (0x1500000 == (0x1500000 & encodedGame) // Diagonal right to left
        || 0xE00000 == (0xE00000 & encodedGame))
     {
        output = "O wins";
     }
     else
     {
        output = "In Progress";
     }
     */
}

// At this point in the exercise I did not want to do "Tie Games".
// Felt that my test cases did not cover as much as I'd like
// I also know that I need to at some point generalise those bit tests.
// Though now I have a better idea of the shape of the data and tests I need to do.

// First of all I put my bit patterns in constants to make sure they were generalised
// Did not write new tests, but did check the above all passed.
// To me this is the real meaning of "refactoring" ;)
// (IE changing internals, no api changes, while making sure there are no regressions.)
/*
 // If this were a bigger grid I would use a for loop or something to figure
 // out flags. But the problem space is limited so why complicate it.
 // Anyway I want to see how constexpr works ;)
 constexpr uint32_t X_WIN_HOR_TOP = 0xE00;
 constexpr uint32_t X_WIN_HOR_MIDDLE = 0xE00 << 3;
 constexpr uint32_t X_WIN_HOR_BOTTOM = 0xE00 << 6;
 constexpr uint32_t O_WIN_HOR_TOP = 0xE00 << 9;
 constexpr uint32_t O_WIN_HOR_MIDDLE = 0xE00 << 12;
 constexpr uint32_t O_WIN_HOR_BOTTOM = 0xE00 << 15;
 
 // Yoda if I guess. Old habits and all that
 if (X_WIN_HOR_TOP == (X_WIN_HOR_TOP & encodedGame)
 || X_WIN_HOR_MIDDLE == (X_WIN_HOR_MIDDLE & encodedGame)
 || X_WIN_HOR_BOTTOM == (X_WIN_HOR_BOTTOM & encodedGame)
 || 0x22200 == (0x22200 & encodedGame) // Diagonal left to right
 )
 {
 output = "X wins";
 }
 else if (O_WIN_HOR_TOP == (O_WIN_HOR_TOP & encodedGame)
 || O_WIN_HOR_MIDDLE == (O_WIN_HOR_MIDDLE & encodedGame)
 || O_WIN_HOR_BOTTOM == (O_WIN_HOR_BOTTOM & encodedGame)
 || 0x1500000 == (0x1500000 & encodedGame) // Diagonal right to left
 )
 {
 output = "O wins";
 }
 else
 {
 output = "In Progress";
 }
 */

// while generalising the diagonals, tests caught this copy and paste error:
/* 
 || O_WIN_DIAG_LEFT == (O_WIN_DIAG_LEFT & encodedGame)
 || O_WIN_DIAG_RIGHT == (O_WIN_DIAG_LEFT & encodedGame)
 */

// Okay I need to test for vertical wins
// As the spec is not checking for number of turns taken by each player etc
// ... just state...
// ... I'm assuming Tic Tac Toes could be some kind of special Terranova
// ... *EXTREME* real time tic tac toe where O was just too slow at going ;)
TEST (XWins, Vertical1xxx)
{
    std::string result;
    
    EXPECT_EQ(37449, evaluateTicTacToes("x--x--x--", result));
    EXPECT_EQ("X wins", result);
    
    // Game eval block now looks like:
    /*
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
     
     // Yoda if I guess. Old habits and all that
     if (X_WIN_HOR_TOP == (X_WIN_HOR_TOP & encodedGame)
     || X_WIN_HOR_MIDDLE == (X_WIN_HOR_MIDDLE & encodedGame)
     || X_WIN_HOR_BOTTOM == (X_WIN_HOR_BOTTOM & encodedGame)
     || X_WIN_DIAG_LEFT == (X_WIN_DIAG_LEFT & encodedGame)
     || X_WIN_DIAG_RIGHT == (X_WIN_DIAG_RIGHT & encodedGame)
     || X_WIN_VERT_LEFT == (X_WIN_VERT_LEFT & encodedGame)
     )
     {
     output = "X wins";
     }
     else if (O_WIN_HOR_TOP == (O_WIN_HOR_TOP & encodedGame)
     || O_WIN_HOR_MIDDLE == (O_WIN_HOR_MIDDLE & encodedGame)
     || O_WIN_HOR_BOTTOM == (O_WIN_HOR_BOTTOM & encodedGame)
     || O_WIN_DIAG_LEFT == (O_WIN_DIAG_LEFT & encodedGame)
     || O_WIN_DIAG_RIGHT == (O_WIN_DIAG_RIGHT & encodedGame)
     )
     {
     output = "O wins";
     }
     else
     {
     output = "In Progress";
     }
*/
}

// Testing my shift assumption here for verticals
TEST (XWins, Vertical2xxx)
{
    std::string result;
    
    EXPECT_EQ(74898, evaluateTicTacToes("-x--x--x-", result));
    EXPECT_EQ("X wins", result);
    
    // Changed very much like the horizontal ones.
    // Horizontal shifts are by 1, then 9 for next player
    /*
     constexpr uint32_t X_WIN_VERT_LEFT = 0x9200;
     constexpr uint32_t X_WIN_VERT_MIDDLE = 0x9200 << 1;
     constexpr uint32_t X_WIN_VERT_RIGHT = 0x9200 << 2;
     constexpr uint32_t O_WIN_VERT_LEFT = 0x9200 << 9;
     constexpr uint32_t O_WIN_VERT_MIDDLE = 0x9200 << 10;
     constexpr uint32_t O_WIN_VERT_RIGHT = 0x9200 << 11;
     */
}

// Okay now pretty confident about horizontal, vertical and diagonal
// Lets go back to the samples for ties

// Testing my shift assumption here for verticals
TEST (SampleTie, Case1)
{
    std::string result;
    
    EXPECT_EQ(26163711, evaluateTicTacToes("ooxxxooxx", result));
    EXPECT_EQ("Tie Game", result);
    /*
     Just added this to top. Thought well, most tic tac toe games are ties
     plus that test is the cheapest.
     
     if (0X1FF == (0X1FF & encodedGame))
     {
        output = "Tie Game";
     }
     */
}

// Testing my shift assumption here for verticals
TEST (SampleTie, Case2)
{
    std::string result;
    
    EXPECT_EQ(45524479, evaluateTicTacToes("oxooxoxox", result));
    EXPECT_EQ("Tie Game", result);
    
    // No code change needed, change for Case1 apparently holds.
}

// At this point I have 10 tests all passing, so am pretty confident
// As I'm getting back in to C++ for the first time in a while
// And never have done C++ 11, please comment on anything that I might
// be brought up in an interview / code review situation.
//
// Thanks again Andy for giving me a nice exercise to focus my learning on
// This made me:
//  * Figure out how to get google test framework working with xcode
//  * Learn enough about xcode to link stuff and test within it
//  * Try out some C++ 11 syntax (the for loop and the constexpr)
//  * Practice TDD for C++
//
// References:
// * http://supernova-at.github.io/candy/candygrams/tic_tacs_toe.html
// * http://en.cppreference.com/w/cpp/language/constexpr
// * http://stackoverflow.com/questions/9438209/for-every-character-in-string
// * http://google-styleguide.googlecode.com/svn/trunk/cppguide.html?showone=Reference_Arguments#Reference_Arguments
// (though I'm on the side of compiler not being magic, but tool with heurstics)
// (aka I do not trust it to the best thing unless I make it totally obvious)
// * http://bitrage.de/wp/google-test-with-xcode-6-and-c11/
//

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
