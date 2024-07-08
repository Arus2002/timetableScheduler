#include "instructor.hpp"
#include <unordered_map>

Instructor::Instructor(const std::string& name, const std::vector<TimeSlot>& availability, const std::vector<Course>& preferredCourses)
    : m_name{name}
    , m_availability{availability}
    , m_preferredCourses{preferredCourses} 
{
    //stugel vor dubliatner chlini courseri
}

void Instructor::displayInfo() const {
    std::cout << "Instructor name: " << m_name << std::endl;
    std::cout << "Instructor available time slots: " << std::endl;
    for (const auto& item: m_availability) {
        std::cout << "[" << item.getStartTime() << " - " << item.getEndTime() << "]" << std::endl; 
    }
    std::cout << "Instructor preferred courses: " << std::endl;
    for (const auto& item: m_preferredCourses) {
        std::cout << item.getName() << std::endl;
    }
}

std::vector<TimeSlot> Instructor::getAvailability() const {
    return m_availability;
}

std::vector<Course> Instructor::getPreferredCourses() const {
    return m_preferredCourses;
}

std::string Instructor::getName() const {
    return m_name;
}

void Instructor::setPreferredCourses(const std::vector<Course>& courses) {
    m_preferredCourses = courses;
}

bool Instructor::isAvailable(const TimeSlot& timeSlot) const {
    for (const auto& slot : m_availability) {
        if (slot == timeSlot) {
            return true;
        }
    }
    return false;
}

bool Instructor::prefersCourse(const Course& course) const {
    for (const auto& prefCourse : m_preferredCourses) {
        if (prefCourse.getName() == course.getName()) {
            return true;
        }
    }
    return false;
}

std::vector<TimeSlot> Instructor::getAssignedTimeSlots() const {
    return m_assignedTimeSlots;
}

bool Instructor::operator==(const Instructor& instructor) const {
    return this->m_name == instructor.m_name;
}

void Instructor::pushTimeSlot(const TimeSlot& timeSlot) {
    m_assignedTimeSlots.push_back(timeSlot);
}

void Instructor::popTimeSlot() {
    m_assignedTimeSlots.pop_back();
}