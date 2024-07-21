#include "course.hpp"

std::size_t CourseHash::operator()(const Course& course) const {
    std::size_t h1 = std::hash<std::string>()(course.getName());
    return h1;
}

bool CourseEqual::operator()(const Course& lhs, const Course& rhs) const {
    return lhs == rhs;
}

Course::Course(const std::string& courseName, const std::vector<TimeSlot>& preferrredTimeSlots)
    : m_courseName{courseName}
    , m_preferredTimeSlots{preferrredTimeSlots} {}

bool Course::operator==(const Course& course) const {
    return this->m_courseName == course.m_courseName;
}

void Course::displayInfo() const {
    std::cout << "Course name: " << m_courseName << std::endl;
    std::cout << "Course preferred time slots: " << std::endl;
    for (const auto& item: m_preferredTimeSlots) {
        std::cout << "[" << item.getStartTime() << " - " << item.getEndTime() << "]" << std::endl; 
    }
}

std::string Course::getName() const {
    return m_courseName;
}

std::vector<TimeSlot> Course::getPreferredTimeSlots() const {
    return m_preferredTimeSlots;
}

json Course::serializeToJson() const {
    json timeSlotsJson;
    for (const auto& timeSlot : m_preferredTimeSlots) {
        timeSlotsJson.push_back(timeSlot.serializeToJson());
    }
    
    return {
        {"m_courseName", m_courseName},
        {"m_preferredTimeSlots", timeSlotsJson}
    };
}

Course Course::deserializeFromJson(const json& courseJson, const std::vector<TimeSlot>& timeSlots) {
    Course deserializedCourse = Course(courseJson.at("m_courseName").get<std::string>(), timeSlots);
    return deserializedCourse;
}