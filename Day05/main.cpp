#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "../Utils/ScopedTimer.h"

bool isOrdered(const std::vector<int>& sequence, const std::unordered_map<int, std::unordered_set<int>>& graph)
{
    // get the position for each value in the sequence
    std::unordered_map<int, int> position;
    for ( int i = 0; i < sequence.size(); ++i ) 
        position[sequence[i]] = i;

    // for each value x in the sequence 
    for ( int x : sequence )
    {
        // get its neighbours/constraints/next pages
        const auto it = graph.find(x);
        if( it == graph.end() ) continue;

        // for each neighbour of x
        for ( int y : it->second )
        {
            //check if its position is above x position (if not it fails the constraint, i.e the second page appears before page x)
            if(position.find(y) != position.end() && position[x] > position[y])
                return false;
        }
    }
    return true;
}

int topologicalSort(const std::vector<int>& nodes, const std::unordered_map<int, std::unordered_set<int>>& graph)
{
    std::vector<int> result;

    std::queue<int> q;
    std::unordered_map<int, int> inDegree;
    for ( int node : nodes ) 
        inDegree[node] = 0;

    for ( int node : nodes ) 
    {
        auto it = graph.find(node);
        if(it == graph.end())
            continue;

        for( int neighbor : it->second)
        {
            if(inDegree.find(neighbor) != inDegree.end())
                inDegree[neighbor]++;
        }
    }

    // get nodes with in-degree of 0
    for(int node : nodes)
    {
        if(inDegree[node] == 0) 
            q.push(node);
    }

    // Sort:
    while( !q.empty() )
    {
        result.push_back(q.front());
        q.pop();

        if( graph.count(result.back()) )
        {
            for(int neighbor : graph.at(result.back()))
            {
                if(inDegree.find(neighbor) == inDegree.end())
                    continue;

                inDegree[neighbor]--;

                if(inDegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }
    }

    // If all nodes are not in result, there's a cycle
    return result.size() == nodes.size() ? result[result.size()/2] : 0;
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

    std::vector<std::vector<int>>                    sequences;
    std::unordered_map<int, std::unordered_set<int>> graph;

    int p1, p2, pos, cur = 0;
    std::string ln;
    while(std::getline(input, ln))
    {
        if(ln.empty()) break;

        pos = ln.find('|');
        graph[ std::stoi(ln.substr(cur, pos)) ].insert( std::stoi( ln.substr(pos+1, ln.size()) ) );
    }

    while(std::getline(input, ln))
    {
        cur = 0; pos = 0;

        sequences.push_back(std::vector<int>());
        for(pos=ln.find(',', cur); pos != std::string::npos; cur=pos+1)
        {
            pos = ln.find(',', cur);
            sequences.back().push_back( std::stoi( 
                ( pos != std::string::npos ) ? ln.substr( cur, pos-cur ) : ln.substr( cur, ln.size() ) 
            ) );   
        }
    }

    input.close();

    

    std::vector<std::vector<int>> badSequences;

    { // Part 1
        ScopedTimer timer;

        int sum = 0;
        for ( const auto& sequence : sequences )
        {
            if(isOrdered(sequence, graph))
                sum += sequence[sequence.size()/2];
            else
                badSequences.push_back(sequence);
        }
        std::cout << sum << std::endl;
    }

    { // Part 2
        ScopedTimer timer;

        int sum = 0;
        for ( const auto& sequence : badSequences )
            sum += topologicalSort(sequence, graph);
        
        std::cout << sum << std::endl;
    }
}