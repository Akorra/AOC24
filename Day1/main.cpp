#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "inc/ScopedTimer.h"

int main()
{
    // Part 1
    {
        ScopedTimer time("Part 1:");

        std::ifstream locationLists("data/location_lists.txt");

        if(!locationLists.is_open())
        {
            std::cerr << "[ERROR] Failed to open file." << std::endl;
            return 1;
        }

        std::vector<int> l1, l2;

        int lid1, lid2;
        while(locationLists >> lid1 >> lid2)
        {
            l1.push_back(lid1);
            l2.push_back(lid2);
        }

        // C++ 20 has ranges
        std::sort(l1.begin(), l1.end());
        std::sort(l2.begin(), l2.end());

        int res = 0;
        for(int i=0; i<l1.size(); ++i)
            res += std::abs(l1[i] - l2[i]);
        
        std::cout << res << std::endl;
    }

    // Part 2
    {
        ScopedTimer time("Part 2:");

        std::ifstream locationLists("data/location_lists.txt");

        if(!locationLists.is_open())
        {
            std::cerr << "[ERROR] Failed to open file." << std::endl;
            return 1;
        }

        std::vector<int> l1;
        std::unordered_map<int, int> l2;

        int lid1, lid2;
        while(locationLists >> lid1 >> lid2)
        {
            l1.push_back(lid1);
            auto it = l2.find(lid2);
            l2[lid2]++;
        }

        int res = 0;
        for(const int& id : l1)
        {
            res += (id * l2[id]);
        }

        std::cout << res << std::endl;    
    }

    return 0;
}