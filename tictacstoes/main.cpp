//
//  main.cpp
//  tictacstoes
//
//  Created by Paul Evans on 8/16/15.
//  Copyright (c) 2015 Paul Evans. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
// For cin and cout
#include <iostream>

#include "tictactoes.h"

int main(int argc, const char * argv[])
{
    if (argc == 1)
    {
        // The one argument is the program location
        // ... so assume console input
        std::cout << "Enter game description (9 characters): ";
        std::string input, output;
        std::cin >> input;
        
        evaluateTicTacToes(input, output);
        std::cout << output << std::endl;
    }
    else
    {
        // Treat each argument as a board description
        std::vector<std::string> args(argv, argv + argc);
        std::string output;
        for (auto i = 1; i < argc; ++i)
        {
            evaluateTicTacToes(args[i], output);
            std::cout << args[i] << "," << output << std::endl;
        }
    }
    
    return 0;
}
