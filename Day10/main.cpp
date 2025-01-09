#include <iostream>

#include "solutions_p1.h"
#include "solutions_p2.h"

int main()
{
    int64_t answer;

    std::cout << "--------- Part 1 ---------\n\n";
    answer = Part1::MySol();
    std::cout << "\nSolution: " << answer << std::endl;

    std::cout << "\n\n--------- Part 2 ---------\n\n";
    answer = Part2::MySol();
    std::cout << "\nSolution: " << answer << std::endl;


    return 0;
}
