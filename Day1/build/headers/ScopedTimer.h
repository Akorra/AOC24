#pragma once

#include <iostream>
#include <string>
#include <chrono>

class ScopedTimer
{
public:
    // Constructor starts the timer and optionally accepts a label
    explicit ScopedTimer(const std::string& label = "") : m_label(label), m_startTime(std::chrono::high_resolution_clock::now())
    { }

    // Destructor stops the timer and prints the elapsed time
    ~ScopedTimer() 
    {
        auto endTime  = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_startTime).count();
        std::cout << "[Timer] " << (m_label.empty() ? "Elapsed Time" : m_label) << ": " << duration / 1000.0 << "ms" << std::endl;
    }

private:
    std::string m_label;
    std::chrono::high_resolution_clock::time_point m_startTime;
};