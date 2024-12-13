#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

int main()
{
    // open file
    std::ifstream input("data/input.txt");
    if(!input.is_open())
    {
        std::cerr << "[ERROR] " << "Opening File";
        return 1;
    }

    std::unordered_map<int, std::unordered_set<int>> nextPages;

    int p1, p2, pos, cur = 0;
    std::string ln;
    while(std::getline(input, ln))
    {
        if(ln.empty())
            break;

        pos = ln.find('|');
        nextPages[ std::stoi(ln.substr(cur, pos)) ].insert( std::stoi(ln.substr(pos+1, ln.size())) );
    }

    std::vector<std::vector<int>> seqs;

    std::string aux;
    while(std::getline(input, ln))
    {
        cur = 0; pos = 0;

        seqs.push_back(std::vector<int>());
        while(pos != std::string::npos)
        {
            pos = ln.find(',', cur);
            aux = ( pos != std::string::npos ) ? ln.substr(cur, pos-cur) : ln.substr(cur, ln.size());
            
            seqs.back().push_back(std::stoi(aux));
            
            cur = pos+1;   
        }
    }

    { // Part 1
        int sum = 0;
        bool badSeq = false;
        for(const auto& seq : seqs)
        {
            badSeq = false;
            for(int i=0; i<seq.size(); ++i)
            {
                for(int j=i+1; j<seq.size(); ++j)
                {
                    auto s = nextPages[seq[j]];
                    if(s.find(seq[i]) != s.end())
                    {
                        badSeq = true;
                        break;
                    }
                }
                if(badSeq)
                    break;
            }
            if(!badSeq)
                sum += seq[seq.size()/2];
        }
        std::cout << sum << std::endl;
    }

    { // Part 2 

    }
}