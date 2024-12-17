#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <cstring>

#include "../Utils/ScopedTimer.h"

#define GUARD    '^'
#define EMPTY    '.'
#define OBSTACLE '#'
#define OBSTRUCT 'O'

enum class Dir : int { UP=0, RIGHT, DOWN, LEFT };
Dir& operator++(Dir& d) { d = static_cast<Dir>( ( (int)d + 1 ) % 4 ); return d; } 

using State = std::pair<int,Dir>;

// transition rules: obstacle -> 90 degrees up->right; right->down; down->left; left->up
constexpr const int directions[4][2] = { {  0, -1 },     // up 
                                         {  1,  0 },     // right
                                         {  0,  1 },     // down
                                         { -1,  0 } };   // left

bool step(State& s, const char* env, const int nrows, const int ncols)
{
    int r = s.first/ncols;
    int c = s.first%ncols;

    int nr = r;
    int nc = c;

    while(true)
    {
        nr = r + directions[(int)s.second][1];
        nc = c + directions[(int)s.second][0];

        // out of bounds
        if( nr < 0 || nc < 0 || nr>=nrows || nc>=ncols)
            return false;

        if(env[nr*ncols + nc] == EMPTY)
            break;

        ++s.second;
    }

    r += directions[(int)s.second][1];
    c += directions[(int)s.second][0];

    s.first = r*ncols + c;

    return true;
}

int main()
{
    // open file
    std::ifstream input("data/input.txt");
    if(!input.is_open())
    {
        std::cerr << "[ERROR] " << "Opening File";
        return 1;
    }

    int nrows = 0, ncols = 0;

    char ch;
    while(input.get(ch))
    {
        if(ch=='\n') break;
        ncols++;
    }    

    nrows = ncols;

    char* grid = new char[nrows*ncols];

    int i=0;
    State start(0, Dir::UP);
    
    input.clear();
    input.seekg(0);
    while(input >> grid[i++])  
    {
        if( grid[i-1] == GUARD )
        { 
            grid[i-1] = EMPTY;
            start.first = i-1;
        }
    }

    input.close();
    
    std::unordered_set<int> path{start.first};

    { // Part 1
        ScopedTimer timer;

        int r, c;
        State st = start;
        while(step(st, grid, nrows, ncols))
            path.emplace(st.first);
    }

    std::cout << path.size() << std::endl;

    int loops = 0;
    { // Part 2
        ScopedTimer timer;

        // keep track of direction
        int* pathState = new int[nrows*ncols];

        // put obstruction on each of the guard's path positions, except start position
        path.erase(start.first);
        for(const auto& obs : path)
        {
            grid[obs] = OBSTRUCT;

            std::memset(pathState, -1, nrows * ncols * sizeof(int));

            auto s = start;
            while(step(s, grid, nrows, ncols))
            {
                if(pathState[s.first] == (int)s.second)
                {
                    //loop
                    loops++;
                    break;
                }
                pathState[s.first] = (int)s.second;
            }

            grid[obs] = EMPTY;
        }
    }

    std::cout << loops << std::endl;

    delete[] grid;
}