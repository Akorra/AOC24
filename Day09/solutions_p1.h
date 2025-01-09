/**
 * @file solutions_p1.h
 * @author Akorra 
 * @brief Includes at least 1 solution for part 1 of the problem, the goal is to compare solutions eficiency
 * for simplicity i/o operations apart from file reading are supressed
 * @version 0.1
 * @date 2025-01-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <fstream>
#include <vector>
#include "../Utils/ScopedTimer.h"

namespace Part1 
{

int64_t MySol() 
{
    ScopedTimer total("My Solution [Total]");

    // no error message for simplicity, read file;
    std::ifstream input("data/input.txt");
    if(!input.is_open())
        return -1;
    
    // we're expecting a single line of data
    std::string block;
    std::getline(input, block);
    
    int64_t sol = 0;
    {
        ScopedTimer st("My Solution");

        // ids can be obtained by halving block position 
        // since we're using the original string and blocks and spaces are alternating, 
        // a memory block id is its position in the string divided by 2)

        int pos=0;
        int e=block.size()-1;
        for(int s=0; s<=e; ++s)
        {
            if(s%2) // space block (odd indices) 
            {
                while(block[s]-->'0')
                {
                    if(block[e]-->'0')
                        sol += (e/2)*(pos++);

                    while(block[e]<'1') e-=2; // move right pointer
                }
            }
            else // memory block (even indices)
            {
                while(block[s]-->'0')
                    sol += (s/2)*(pos++);
            }
        }

    }

    return sol;
}

};