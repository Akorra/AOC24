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
#include <unordered_map>
#include <map>
#include <math.h>
#include <span>
#include <queue>
#include <functional>
#include <numeric>
#include "../Utils/ScopedTimer.h"

#define count_digits(x) std::log10(x)+1

namespace Part2
{

struct stone
{
    bool     found_splitz = false;
    int64_t to_splitz    = 0;
    int64_t left, right;
    int64_t value;

    // to get the stone we should use for jump aheads:
    bool operator<(const stone& s) const
    {
        if(to_splitz < s.to_splitz) return true;
        if(to_splitz > s.to_splitz) return false;
        if(left < s.left) return true;
        if(left > s.left) return false;
        if(right < s.right) return true;
        if(right > s.right) return false;
        return (value < s.value);
    }
};

stone find_splitzville(int64_t s)
{
    int64_t n, p, iter = 0, source = s;

    if (!s) { s = 1; iter = 1; }

    while ((n = count_digits(s)) % 2) {
        s *= 2024;
        ++iter;
    }

    p = std::pow<int64_t>(10, n/2);
    return stone{
        .found_splitz = true,
        .to_splitz = iter,
        .left  = s/p,
        .right = s%p,
        .value = source
    };
}

int64_t MySol(int64_t nBlinks)
{
    ScopedTimer timer("total");

    // open file for reading;
    std::ifstream input("data/input.txt");
    if(!input.is_open())
        return 0;

    //read file int by int to get roots
    u_int64_t n;
    std::vector<int64_t>  stones;
    while(input >> n)
        stones.emplace_back(n);

    // map stone value at blink to respective expanded number of stones
    std::unordered_map<int64_t, stone> memory;

    int64_t sum = 0;
    {
        ScopedTimer st("");

        //initialize search
        std::map<stone, int64_t> stone_count;
        for(const auto& s : stones)
        {
            if(!memory.contains(s))
                memory[s] = find_splitzville(s);
            ++stone_count[memory[s]];
        }

        int64_t blink=0;
        while(nBlinks>0)
        {
            int64_t blinks = stone_count.begin()->first.to_splitz+1;
            std::map<stone, int64_t> curr_stones;

            for(auto& [s, count] : stone_count)
            {
                if(s.to_splitz - blinks < 0)
                {
                    if(!memory.contains(s.left))  memory[s.left] = find_splitzville(s.left);
                    if(!memory.contains(s.right)) memory[s.right] = find_splitzville(s.right);

                    curr_stones[memory[s.left]]  += count;
                    curr_stones[memory[s.right]] += count;
                }
                else
                {
                    int64_t ns = s.value ? s.value*2024 : 1;
                    if(!memory.contains(ns))
                        memory[ns] = stone { .found_splitz = true, .to_splitz = static_cast<uint8_t>(s.to_splitz - blinks), .left =  s.left, .right = s.right, .value = ns };
                    curr_stones[memory[ns]] += count;
                }
            }
            nBlinks -= blinks;
            std::swap(stone_count, curr_stones);
        }

        sum = std::transform_reduce(stone_count.begin(), stone_count.end(), 0ULL, std::plus(), [](auto & val){ return val.second; });
    }
    return sum;
}

};
