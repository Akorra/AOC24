#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

int main()
{
    // open file
    std::ifstream input("data/input.txt");
    if(!input.is_open())
    {
        std::cerr << "[ERROR] " << "Opening File";
        return 1;
    }

    //read file into buffer
    std::stringstream buffer;
    buffer << input.rdbuf();

    std::string data = buffer.str();

    { // Part 1&2
        // Regex to match mul(x,y) where x and y are 1-3 digits
        std::regex mulRegex(R"((mul\((\d{1,3})\s*,\s*(\d{1,3})\))|(do\(\))|(don\'t\(\)))");

        // smatch
        // 0  full batch
        // 1  mul(x,y)
        // 2  x
        // 3  y
        // 4  do()
        // 5  don't()
        
        bool allowNextMul = true;
        long long sum = 0;
        auto start = data.cbegin(); //read only pointer
        for(std::smatch m; std::regex_search(start, data.cend(), m, mulRegex);)
        {
            if(m.size() > 6)
                std::cout << m.size() << std::endl;
            if(!(m[1].matched || m[2].matched || m[3].matched || m[4].matched || m[5].matched))
                    std::cout << m[0].str() << std::endl;

            if(m[1].matched && allowNextMul)
                sum += ( std::stoi( m[2].str() ) * std::stoi( m[3].str() ) ); 

            if(m[4].matched)
                allowNextMul = true;
            if(m[5].matched)
                allowNextMul = false;
            
            start = m.suffix().first;
        }

        std::cout << sum << std::endl;
    }

    return 0;
}