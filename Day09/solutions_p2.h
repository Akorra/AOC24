/**
 * @file solutions_p2.h
 * @author Akorra 
 * @brief Includes at least 1 solution for part 2 of the problem, the goal is to compare solutions eficiency
 * for simplicity i/o operations apart from file reading are supressed
 * @version 0.1
 * @date 2025-01-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <fstream>
#include <vector>
#include <tuple>

#include "../Utils/ScopedTimer.h"

namespace Part2
{

struct Block 
{
    Block(const int start_idx, const int size, const int value) : start_idx(start_idx), size(size), value(value) {}
    int start_idx;
    int size;
    int value;

    std::tuple<Block, Block> split(const int size_in, const int value_in) const 
    {
        return { Block(start_idx, size_in, value_in), Block(start_idx + size_in, size - size_in, -1) };
    }
};

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

    int ptr = 0;
    std::vector<Block> blocks;
    for (int i=0; i<block.length(); ++i) 
    {
        blocks.emplace_back(ptr, block[i]-'0', (i%2) ? -1 : (i/2));
        ptr += (block[i]-'0');
    }

    int64_t sol = 0;
    {
        ScopedTimer st("My Solution");

        int right = blocks.size() - 1;
        for (int right=blocks.size()-1;  right>0; right--) 
        {
            if (blocks[right].value < 0) 
            {
                right--;
                continue;
            }
        
            for (int left= 0; left<right; left++) 
            {
                if (blocks[left].value == -1 && blocks[left].size >= blocks[right].size) 
                {
                    const auto [b1, b2] = blocks[left].split(blocks[right].size, blocks[right].value);
                    blocks[left] = b1;
                    blocks[right].value = -1;
                    blocks.insert(std::begin(blocks) + left + 1, b2);
                    break;
                }
            }
        }

        ptr = 0;
        for (const auto& b : blocks) {
            if (b.value != - 1) {
                for (int i = 0; i < b.size; i++, ptr++) {
                    sol += ptr * b.value;
                }
            } else {
                ptr += b.size;
            }
        }
    }

    return sol;
} 

};