#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "../Utils/ScopedTimer.h"

#define EMPTY '.'

int main()
{
    std::ifstream input("data/input.txt");
    if(!input.is_open())
    {
        std::cerr << "[ERROR] " << "Opening File";
        return -1;
    }

    int nrows=0, ncols=0;
    
    std::unordered_map<char, std::vector<int>> antennas;

    char ch;

    int i=0;
    while(input.get(ch))
    {
        if(ch != '\n') 
        {
            if(ch != EMPTY)
                antennas[ch].push_back(i);
            i++;
        }
        else
        {
            nrows++;
        }
    }
    nrows++; //EOF does not contain '\n'
    ncols = nrows;

    input.close();

    std::unordered_set<int> antinodes;
    {
        ScopedTimer timer("Part 1");

        int r, c, dr, dc;
        for(const auto& [antenna, locations] : antennas)
        {
            for(int i=0; i<locations.size(); ++i)
            {   
                for(int j=i+1; j<locations.size(); ++j)
                {
                    dr = locations[i]/ncols - locations[j]/ncols;
                    dc = locations[i]%ncols - locations[j]%ncols;

                    r = locations[i]/ncols + dr;
                    c = locations[i]%ncols + dc;
                    if(r>-1 && r<nrows && c>-1&&c<ncols)
                        antinodes.emplace(r*ncols+c);

                    r = locations[i]/ncols - 2*dr;
                    c = locations[i]%ncols - 2*dc;
                    if(r>-1 && r<nrows && c>-1&&c<ncols)
                        antinodes.emplace(r*ncols+c);
                }
            }
        }
    }
    std::cout << antinodes.size() << std::endl;

    antinodes.clear();
    {
        ScopedTimer timer("Part 2");
        int r, c, dr, dc;
        for(const auto& [antenna, locations] : antennas)
        {
            for(int i=0; i<locations.size(); ++i)
            {   
                for(int j=i+1; j<locations.size(); ++j)
                {

                    dr = locations[i]/ncols - locations[j]/ncols;
                    dc = locations[i]%ncols - locations[j]%ncols;

                    r = locations[i]/ncols;
                    c = locations[i]%ncols;

                    while(r>-1 && r<nrows && c>-1 && c<ncols) {
                        antinodes.emplace(r*ncols+c);
                        r+=dr; c+=dc;
                    } 

                    r = locations[i]/ncols;
                    c = locations[i]%ncols;
                    
                    while(r>-1 && r<nrows && c>-1 && c<ncols) {
                        antinodes.emplace(r*ncols+c);
                        r-=dr; c-=dc;
                    }
                }
            }
        }
    }
    std::cout << antinodes.size() << std::endl;    
    
    return 0;
}