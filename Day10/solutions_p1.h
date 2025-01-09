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
#include <tuple>
#include <vector>
#include <unordered_set>
#include <queue>
#include "../Utils/ScopedTimer.h"

namespace Part1
{
void DFS(int pos, const std::vector<int>& map, const int rows, const int cols, std::unordered_set<int>& goals)
{
  const int row = pos / cols;
  const int col = pos % cols;
  const int height = map[pos];
  if(height == 9)
  {
    goals.insert(pos);
    return;
  }

  int score = 0;
  if(row + 1 < rows && map[pos+cols] == height + 1) // down
    DFS(pos+cols, map, rows, cols, goals);
  if(col + 1 < cols && map[pos+1] == height + 1) // right 
    DFS(pos+1, map, rows, cols, goals);
  if(col > 0 && map[pos-1] == height + 1) // left
    DFS(pos-1, map, rows, cols, goals);
  if(row > 0 && map[pos-cols] == height + 1) // up
    DFS(pos-cols, map, rows, cols, goals);
}

int MySol()
{
  ScopedTimer total("Part1 - Total");

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

  std::unordered_set<int> unique_goals, visited;
  int64_t sum = 0;
  {
    ScopedTimer st("Part 1");
    for(const int head : trailHeads)
    {
      unique_goals.clear();
      DFS(head, map, rows, cols, unique_goals);
      sum += unique_goals.size();
    }
  }

  return sum;
}

int BFS()
{
  ScopedTimer total("Part1 - BFS - Total");

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

  int directions[4] = {cols, -cols, 1, -1}; // increments for 2D adjacency (right, left, down, up) 

  int64_t sum = 0;
  {
    ScopedTimer st("Part 1 - BFS");

    // for each trail head (9)
    std::unordered_set<int> visited, unique_goals;
    for(const int head : trailHeads) 
    {
      visited.clear();
      unique_goals.clear();

      //perform BFS to find goal positions (9)
      std::queue<int> q;

      // insert/visit trail head
      q.push(head);
      visited.insert(head);

      // BFS
      while(!q.empty())
      {
        // get current node 
        int pos = q.front();
        q.pop(); //remove from q

        int height = map[pos];
        if(height == 9) 
        {
          // found goal position, stop search
          unique_goals.insert(pos);
          continue;
        }

        int row = pos/cols;
        int col = pos%cols;
        
        // search adjacency 
        for(int d=0; d<4; ++d)
        {
          int p = pos + directions[d];
          if(p < 0 || p >= map.size())    continue; // out of bounds;
          if(d == 2 && (col + 1) >= cols) continue; // right boundary
          if(d == 3 && (col - 1)  < 0)    continue; // left boundary

          // do not re-visit and only visit +1 height increments
          if(!visited.count(p) && map[p] == height + 1)
          {
            visited.insert(p);
            q.push(p);
          }
        }
      }
      
      sum += unique_goals.size(); // add score
    }
  }

  return sum;
}

};
