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
#include <math.h>
#include <queue>
#include "../Utils/ScopedTimer.h"

namespace Part1
{

int MySol(int nBlinks)
{
  ScopedTimer total("Part1 - Total");
  // open file for reading;
  std::ifstream input("data/input.txt");
  if(!input.is_open())
    return 0;

  //read file int by int
  u_int64_t n;
  std::vector<u_int64_t>  stones;
  while(input >> n)
    stones.emplace_back(n);

  {
    ScopedTimer st("Part1");

    int blinks = nBlinks;
    while(blinks-->0)
    {
      for(int s=0; s<stones.size(); ++s)
      {
        if(stones[s] == 0)
        {
          stones[s] = 1;
          continue;
        }

        n = std::log10(stones[s])+1; // num digits
        if(n%2) // if 0 then it has even number of digits so step over this (0 == false)
        {
          stones[s] *= 2024;
          continue;
        }

        int p = std::pow(10, n/2);
        stones.insert(stones.begin() + s + 1, stones[s]%p); // insert second half
        stones[s] /= p;
        s++; //step to next stone, so loop proceeds normaly
      }
    }
  }
  return stones.size();
}

//! Tre expansion solution --------------------------------------------------------

int expandNodeDFS(u_int64_t node, int lvl, const int& max)
{
  if(lvl == max)
    return 1;

  if(node == 0)
    return expandNodeDFS(1, lvl+1, max);

  int n = std::log10(node)+1; // num digits
  if(n%2) // if 0 then it has even number of digits so step over this (0 == false)
    return expandNodeDFS(node*2024, lvl+1, max);

  int p = std::pow(10, n/2);
  return expandNodeDFS(node/p, lvl+1, max) + expandNodeDFS(node%p, lvl+1, max);
}

// lets look at this as expanding severall trees to level #blinks
int64_t TreeExpansion(int nBlinks)
{
  ScopedTimer total("Part1 Tree - Total");

  // open file for reading;
  std::ifstream input("data/input.txt");
  if(!input.is_open())
    return 0;

  //read file int by int to get roots
  u_int64_t n;
  std::vector<u_int64_t>  stones;
  while(input >> n)
    stones.emplace_back(n);

  int num_stones = 0;
  {
    ScopedTimer total("Part1 Tree- Total");

    for(auto& node : stones)
      num_stones += expandNodeDFS(node, 0, nBlinks);
  }

  return num_stones;
}

};
