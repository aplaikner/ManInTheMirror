
#ifndef MANINTHEMIRROR_TIMER_H
#define MANINTHEMIRROR_TIMER_H

#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();
    void Stop();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};


#endif //MANINTHEMIRROR_TIMER_H
