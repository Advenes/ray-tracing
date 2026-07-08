
#pragma once
#include <chrono>

class timer {
    public:


     void start_timer() {
        start = std::chrono::steady_clock::now();
    }

     std::chrono::milliseconds stop_timer() {
        end = std::chrono::steady_clock::now();
        return (std::chrono::duration_cast<std::chrono::milliseconds>(end - start));
    }



private:
     std::chrono::time_point<std::chrono::steady_clock> start;
     std::chrono::time_point<std::chrono::steady_clock> end;

};