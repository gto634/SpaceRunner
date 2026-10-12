#include "IntervalClock.h"

IntervalClock::IntervalClock() {
	m_interval = 0;
	m_elapseTime = 0;
}

IntervalClock::IntervalClock(float v_interval) {
	m_interval = v_interval;
	m_elapseTime = 0;
}

void IntervalClock::SetInterval(float v_interval) {
	m_interval = v_interval;
}

float IntervalClock::GetTime() {
	return m_elapseTime;
}

float IntervalClock::GetTimeInverse() {
	return m_interval - m_elapseTime;
}

bool IntervalClock::Update(float deltatime) {
	m_elapseTime += deltatime;
	return IsFinished();
}

void IntervalClock::Restart() {
	m_elapseTime = 0;
}

bool IntervalClock::IsFinished() {
	return (m_elapseTime >= m_interval);
}