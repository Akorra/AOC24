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
#include <tuple>
#include <vector>
#include <unordered_set>
#include <queue>
#include "../Utils/ScopedTimer.h"

namespace Part2
{
int DFS(int pos, const std::vector<int>& map, const int rows, const int cols)
{
    const int row = pos / cols;
    const int col = pos % cols;
    const int height = map[pos];
    if(height == 9)
        return 1;

    int score = 0;
    if(row + 1 < rows && map[pos+cols] == height + 1) // down
        score += DFS(pos+cols, map, rows, cols);
    if(col + 1 < cols && map[pos+1] == height + 1) // right 
        score += DFS(pos+1, map, rows, cols);
    if(col > 0 && map[pos-1] == height + 1) // left
        score += DFS(pos-1, map, rows, cols);
    if(row > 0 && map[pos-cols] == height + 1) // up
        score += DFS(pos-cols, map, rows, cols);
    return score;
}

int MySol()
{
  ScopedTimer total("Part2 - Total");

  // open file for reading;
  std::ifstream input("data/input.txt");
  if(!input.is_open())
    return 0;

  // generate map(grid) and trail heads from file
  int rows=0, cols=0;
  std::vector<int>  map;        //flattened grid
  std::vector<int>  trailHeads; //flat id for trail heads
  
  //read file line by line
  std::string ln;
  while(std::getline(input, ln))
  {
    for(int c=0; c<ln.size(); ++c) // loop through string characters
    {
      map.emplace_back(ln[c]-'0'); // populate map (character - '0' gives corresponding decimal value)
      if(ln[c] == '0') // zeros are trail heads
          trailHeads.push_back(rows*ln.size() + c);
    }
    rows++; //increment number of height values along y (number of rows)
  }
  cols = ln.size(); // length of string can inform about number of columns (i.e. height values along x)

  int64_t sum = 0;
  {
    ScopedTimer st("Part 2");
    for(const int head : trailHeads)
      sum += DFS(head, map, rows, cols);
  }

  return sum;
}
};
