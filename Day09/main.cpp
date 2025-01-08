#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

#include "../Utils/ScopedTimer.h"

#define EMPTY '.'

void swap()
{

}

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

int main()
{
    ScopedTimer timer("Total");

    std::ifstream input("data/input.txt");
    if(!input.is_open())
    {
        std::cerr << "[ERROR] " << "Opening File";
        return -1;
    }

    // Expecting a single line file 
    std::string block;
    std::getline(input, block);
    std::string block2 = block;
    ;
    int ptr = 0, sz=0;
    std::vector<Block> blocks;
    for (int i=0; i<block.length(); ++i) 
    {
        blocks.emplace_back(ptr, block[i]-'0', (i%2) ? -1 : (sz++));
        ptr += (block[i]-'0');
    }
    
    int64_t sum = 0;
    {
        ScopedTimer timer("Part 1");

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
                        sum += (e/2)*(pos++);

                    while(block[e]<'1') e-=2; // move right pointer
                }
            }
            else // memory block (even indices)
            {
                while(block[s]-->'0')
                    sum += (s/2)*(pos++);
            }
        }
    }
    std::cout << std::endl << sum << std::endl;

    sum = 0;
    {
        ScopedTimer timer("Part 2");

        int r = blocks.size() - 1;
        while (r > 0) 
        {
            if (blocks[r].value == -1) 
            {//test
                r--;
                continue;
            }
        
            for (int l = 0; l < r; l++) 
            {
                if (blocks[l].value == -1 && blocks[l].size >= blocks[r].size) 
                {
                    const auto [b1, b2] = blocks[l].split(blocks[r].size, blocks[r].value);
                    blocks[l] = b1;
                    blocks[r].value = -1;
                    blocks.insert(std::begin(blocks) + l + 1, b2);
                    break;
                }
            }
            r--;
        }

        r = 0;
        for (const auto& b : blocks) {
            if (b.value != - 1) {
                for (int i = 0; i < b.size; i++, r++) {
                    sum += r * b.value;
                }
            } else {
                r += b.size;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}