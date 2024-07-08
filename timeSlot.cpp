#include "timeSlot.hpp"
#include <unordered_map>

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

void TimeSlot::timeSlotChecker() const {
    if (m_startTime.size() != 5 || m_startTime.size() != 5) {
        std::cout << "Invalid time slot1!" << std::endl;
        return;
    }
    for (int i = 0; i < m_startTime.size() && m_startTime.size(); ++i) {
        if (i == 2 && (m_startTime[i] != ':' || m_endTime[i] != ':')) {
            std::cout << "Invalid time slot2!" << std::endl;
            return;
        }
        else if (i == 0 && (m_startTime[i] > '2' || m_startTime[i] < '0' ||
                            m_endTime[i] > '2' || m_endTime[i] < '0')) {
            
            std::cout << "Invalid time slot!3" << std::endl;
            return;
        }
        else if (i == 0 && ((m_startTime[i] == '2' && m_startTime[i + 1] > '4') ||
                            (m_endTime[i] == '2' && m_endTime[i + 1] > '4'))) {
            std::cout << "Invalid time slot!4" << std::endl;
            return;
        }
        else if (i == 1 && (m_startTime[i] > '9' || m_startTime[i] < '0' ||
                            m_endTime[i] > '9' || m_endTime[i] < '0')) {
            
            std::cout << "Invalid time slot!5" << std::endl;
            return;
        }
        else if ((i == 3 || i == 4) && (m_startTime[i] != '0' ||
                                        m_endTime[i] != '0')) {

            std::cout << "Invalid time slot!6" << std::endl;
            return;
        }
        
        std::string startTimeHour = m_startTime.substr(0, 2);
        std::string endTimeHour = m_endTime.substr(0, 2);
        int startTimeInteger = std::stoi(startTimeHour);
        int endTimeInteger = std::stoi(endTimeHour);
        if (endTimeInteger - startTimeInteger != 1) {
            std::cout << "Invalid time slot!7" << std::endl;
            return;
        }
    }

    std::unordered_map<std::string, int> days = {
        {"Monday", 1},
        {"Tuesday", 2},
        {"Wednesday", 3},
        {"Thursday", 4},
        {"Friday", 5},
        {"Saturday", 6},
        {"Sunday", 7}
    };

    if (days.find(m_day) == days.end()) {
        std::cout << "Invalid time slot!8" << std::endl;
        return;
    }
}