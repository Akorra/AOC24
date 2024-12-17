#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include "../Utils/ScopedTimer.h"


bool getEquation(const std::string& str, unsigned long& result, std::vector<int>& values)
{
    int pos = str.find(':');
    if(pos == std::string::npos)
        return false;

    values.clear();

    result = std::stoul(str.substr(0, pos));

    // account for space after ':'
    for(int cur=pos+2; pos!=std::string::npos; pos=str.find(' ', cur), cur = pos+1)
        values.push_back( std::stoi(str.substr(cur, (pos != std::string::npos) ? pos : str.size() ))); 

    return true;
}

//BFS
bool findOperators(const unsigned long goal, std::vector<int>& values)
{
    int depth = values.size(); 

    std::queue<unsigned long> q;

    q.push(values[0]);

    int count = 0;
    for(int lvl = 0; lvl < depth; ++lvl)
    {
        int nNodes = q.size();

        for(int n=0; n<nNodes; ++n)
        {
            unsigned long cur = q.front();
            q.pop();

            if(lvl < depth-1)
            {
                q.push(cur + values[lvl+1]);
                q.push(cur * values[lvl+1]);
            }
            else if(cur == goal)
            {
                return true;
            }
        }
    }
    return false;
}

unsigned long concat( unsigned long a, unsigned long b)
{
    unsigned long c = b;
    while(c != 0u)
    {
        c /=10;
        a *=10;
    }

    return a+b;
}

template<bool concatenate = false>
bool findOperators(const unsigned long goal, unsigned long res, const std::vector<int>& values, int lvl)
{
    if(lvl == values.size() - 2)
        return ( res + values[lvl+1] ) == goal || ( res * values[lvl+1] ) == goal || ( concatenate && (concat(res, values[lvl+1]) == goal) );
    
    if(findOperators<concatenate>(goal, res+values[lvl+1], values, lvl+1))
        return true;
    if(findOperators<concatenate>(goal, res*values[lvl+1], values, lvl+1))
        return true;
    if(concatenate && findOperators<concatenate>(goal, concat(res, values[lvl+1]), values, lvl+1))
        return true;

    return false;
}


int main()
{
    // open file
    std::ifstream input("data/input.txt");
    if(!input.is_open())
    {
        std::cerr << "[ERROR] " << "Opening File";
        return -1;
    }

    unsigned long sum = 0;
    { // Part 1
        ScopedTimer timer("Part 1");

        unsigned long res;
        std::vector<int> eq;

        int f = 0;
        
        std::string ln;
        while(std::getline(input, ln))
        {
            if(getEquation(ln, res, eq))
            {
                if(findOperators<false>(res, eq[0], eq, 0))
                    sum += res;
            }
        }
    }
    std::cout << sum << std::endl;

    input.clear();
    input.seekg(0);
    sum = 0;
    { // Part 2
        ScopedTimer timer("Part 2");

        unsigned long res;
        std::vector<int> eq;

        int f = 0;
        
        std::string ln;
        while(std::getline(input, ln))
        {
            if(getEquation(ln, res, eq))
            {
                if(findOperators<true>(res, eq[0], eq, 0))
                    sum += res;
            }
        }
    }
    std::cout << sum << std::endl;

    input.close();

    return 0;
}