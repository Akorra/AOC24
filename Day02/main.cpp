#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../Utils/ScopedTimer.h"

bool isSafe(const std::string& report, int startpos = 0, bool dampenerOn=false) 
{   
    bool dec=false, inc=false;
    int dist=0;
    int num, prev;
    
    int aux = startpos;
    int cur = startpos;
    int pos = report.find(' ');

    prev = (pos != std::string::npos) ? std::stoi(report.substr(cur, pos)) : std::stoi(report.substr(cur));

    while(pos != std::string::npos)
    {
        aux = cur;
        cur = pos+1;
        pos = report.find(' ', cur);

        try {
            num = (pos != std::string::npos) ? std::stoi(report.substr(cur, pos)) : std::stoi(report.substr(cur));
        } catch(const std::invalid_argument& e) {
            break;
        }
        dist = std::abs(num - prev);
        if(num > prev)
            inc = true;
        else if(num < prev)
            dec = true;

        if(dist > 3 || dist < 1 || (inc && dec))
        {
            if(dampenerOn)
            {
                std::string str1 = report;
                str1.erase(aux, cur-aux);
                if(isSafe(str1, 0, false))
                    return true;

                std::string str2 = report;
                str2.erase(cur, pos-cur+1);
                if(isSafe(str2, 0, false))
                    return true;
            }
            
            return false;
        }

        prev = num;
    }

    return true;
}

bool isInc(const std::vector<int32_t>& data, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i) {
        if (data[i] < data[i - 1] + 1 || data[i] > data[i - 1] + 3) {
            return false;
        }
    }
    return true;
}

bool isDec(const std::vector<int32_t>& data, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i) {
        if (data[i - 1] < data[i] + 1 || data[i - 1] > data[i] + 3) {
            return false;
        }
    }
    return true;
}

bool check2(const std::vector<int32_t>& data)
{
    // skip the i-th value and check the split intervals and the two newly joined neighbours
    for (size_t i = 0; i < data.size(); ++i) {
        const auto join = (i > 0 && i < data.size() - 1) ? std::vector<int32_t>{data[i - 1], data[i + 1]} : std::vector<int32_t>{};
        if (isInc(data, 1, i) && isInc(join, 1, join.size()) && isInc(data, i + 2, data.size()))
            return true;
        if (isDec(data, 1, i) && isDec(join, 1, join.size()) && isDec(data, i + 2, data.size()))
            return true;
    }
    return false;
}

int main() 
{
    { // Part 1
        ScopedTimer timer("Part1");

        std::ifstream reports("data/reports.txt");
        if(!reports.is_open())
        {
            std::cerr << "[ERROR] Failed to open file." << std::endl;
            return 1;
        }

        int safeCount = 0;

        std::string report;
        while(std::getline(reports, report))
        {
            if(report.empty())
                continue;
            if(isSafe(report))
                safeCount++;
        }

        std::cout << safeCount << std::endl;
    }

    { // Part2
        ScopedTimer timer("Part2");

        std::ifstream reports("data/reports.txt");
        if(!reports.is_open())
        {
            std::cerr << "[ERROR] Failed to open file." << std::endl;
            return 1;
        }

        int safeCount = 0;

        std::string report;
        while(std::getline(reports, report))
        {
            if(report.empty())
                continue;
            

            if(isSafe(report, 0, true))
                safeCount++;
        }

        std::cout << safeCount << std::endl;
    }

    return 0;
}