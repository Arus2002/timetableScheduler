#include "course.hpp"

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

void Course::setPreferredTimeSlots(const std::vector<TimeSlot>& timeSlots) {
    m_preferredTimeSlots = timeSlots;
}