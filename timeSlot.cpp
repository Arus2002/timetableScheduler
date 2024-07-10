#include "timeSlot.hpp"
#include <unordered_map>

std::size_t TimeSlotHash::operator()(const TimeSlot& s) const {
    std::size_t h1 = std::hash<std::string>()(s.getStartTime());
    std::size_t h2 = std::hash<std::string>()(s.getEndTime());
    std::size_t h3 = std::hash<std::string>()(s.getDay());

    return h1 ^ (h2 << 1) ^ (h3 << 2);
}

bool TimeSlotEqual::operator()(const TimeSlot& lhs, const TimeSlot& rhs) const {
    return lhs == rhs;
}

TimeSlot::TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime)
    : m_day{day}
    , m_startTime{startTime}
    , m_endTime{endTime} {}

bool TimeSlot::operator==(const TimeSlot& other) const {
    return this->m_startTime == other.m_startTime && this->m_endTime == other.m_endTime && this->m_day == other.m_day;
}

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

json TimeSlot::serializeToJson() const {
    return json{{"m_day", m_day}, 
                {"m_startTime", m_startTime}, 
                {"m_endTime", m_endTime}};
}

TimeSlot TimeSlot::deserializeFromJson(const json& timeSlotJson) {
    TimeSlot deserializedTimeSlot = TimeSlot(timeSlotJson.at("m_day").get<std::string>(),
        timeSlotJson.at("m_startTime").get<std::string>(),
        timeSlotJson.at("m_endTime").get<std::string>());
    return deserializedTimeSlot;
}