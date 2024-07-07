#include "timeSlot.hpp"

TimeSlot::TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime)
    : m_day{day}
    , m_startTime{startTime}
    , m_endTime{endTime} {}

void TimeSlot::displayInfo() const {
    std::cout << "Time slot day: " << m_day << std::endl;
    std::cout << "Time slot start time: " << m_startTime << std::endl;
    std::cout << "Time slot end time: " << m_endTime << std::endl;
}

std::string TimeSlot::getStartTime() const {
    return m_startTime;
}

std::string TimeSlot::getEndTime() const {
    return m_endTime;
}

std::string TimeSlot::getDay() const {
    return m_day;
}

bool TimeSlot::operator==(const TimeSlot& other) const {
    return this->m_startTime == other.m_startTime && this->m_endTime == other.m_endTime && this->m_day == other.m_day;
}