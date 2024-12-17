#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

#include "../Utils/ScopedTimer.h"

#define EMPTY    '.'
#define OBSTACLE '#'

enum class Dir : int { UP=0, RIGHT, DOWN, LEFT };
Dir& operator++(Dir& d) { d = static_cast<Dir>( ( (int)d + 1 ) % 4 ); return d; } 

using State = std::pair<int,Dir>;

// transition rules: obstacle -> 90 degrees up->right; right->down; down->left; left->up
constexpr const int directions[4][2] = { {  0, -1 },     // up 
                                         {  1,  0 },     // right
                                         {  0,  1 },     // down
                                         { -1,  0 } };   // left

#define ns(state, action, row) state+directions[action][row]
bool step(State& s, const char* env, const int nrows, const int ncols)
{

    int r = s.first/ncols;
    int c = s.first%ncols;

    int nr = r + directions[(int)s.second][1];
    int nc = c + directions[(int)s.second][0];
    
    // out of bounds
    if( nr < 0 || nc < 0 || nr>=nrows || nc>=ncols)
        return false;

    if ( env[ ( r+directions[(int)s.second][1] )*ncols + ( c+directions[(int)s.second][0] ) ] == OBSTACLE )
        ++s.second;

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
        ncols++;
        if(ch=='\n')
            break;
    }    

    nrows = ncols;

    char* grid = new char[nrows*ncols];
    
    int i=0;
    State start(0, Dir::UP);
    
    input.seekg(0);
    while(input.get(ch)) 
    {
        if(!( ch - '^' )) { grid[i] = EMPTY; start.first = i; }
        grid[i++] = ch; 
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

    { // Part 2
        ScopedTimer timer;
    }
}