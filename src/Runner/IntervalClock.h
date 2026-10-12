#pragma once

class IntervalClock {
private:
    float m_elapseTime;
    float m_interval;

public:

    IntervalClock();
    IntervalClock(float v_interval);
    void SetInterval(float v_interval);

    float GetTime();
    float GetTimeInverse();

    void Restart();
    bool Update(float deltatime);
    bool IsFinished();
};