#include <iostream>
#include <fstream>

const int directions[8][2] = {
    {0, 1},   // right
    {1, 0},   // down
    {0, -1},  // left
    {-1, 0},  // up
    {1, -1},  // down-left diagonal
    {-1, 1},  // up-right diagonal
    {1, 1},   // down-right diagonal
    {-1, -1}  // up-left diagonal
};

// Function to check if the word "XMAS" starts at the flattened index idx
bool checkWord(char* grid, int idx, int m, int n, const std::string& word, int di, int dj) {
    for (int k = 0; k < word.size(); ++k) {
        int ni = (idx / n) + k * di;  // Calculate the new row from flattened index
        int nj = (idx % n) + k * dj;  // Calculate the new column from flattened index
        
        // Check if the position is within bounds and if the character matches
        if (ni < 0 || ni >= m || nj < 0 || nj >= n || grid[ni * n + nj] != word[k]) {
            return false;
        }
    }
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

    std::string ln;
    std::getline(input, ln);

    int nrows = ln.size(); 
    int ncols = nrows; 
    char* grid = new char[nrows*ncols];

    input.clear();
    input.seekg(0);
    for(int i=0; input >> grid[i++];) {}

    { // Part 1
        int count = 0;
        // Traverse all cells in the flattened grid (from 0 to m*n-1)
        for (int idx = 0; idx < nrows * ncols; ++idx) 
        {
            // If the current cell corresponds to 'X', check all 8 possible directions
            if (grid[idx] == 'X') 
            {
                for (int d = 0; d < 8; ++d) 
                {
                    int di = directions[d][0];
                    int dj = directions[d][1];
                    if (checkWord(grid, idx, nrows, ncols, "XMAS", di, dj))
                        ++count;
                }
            }
        }

        std::cout << count << std::endl; 
    }

    { // Part 2 - filter

        int r,c, count=0;
        for(int r=1; r<nrows-1; ++r)
        {
            for(int c=1; c<ncols-1; ++c)
            {
                if(grid[r*ncols+c] == 'A' && ( grid[(r-1)*ncols+c-1] + grid[(r+1)*ncols+c+1] == 160 ) && ( grid[(r+1)*ncols+c-1] + grid[(r-1)*ncols+c+1] == 160 ) )
                    count++;
            }
        }

        std::cout << count << std::endl;
    }
}