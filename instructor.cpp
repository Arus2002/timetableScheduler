#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP

#include "instructor.hpp"
#include <unordered_map>

Instructor::Instructor(const std::string& name, const std::vector<TimeSlot>& availability, const std::vector<Course>& preferredCourses)
    : m_name{name}
    , m_availability{availability}
    , m_preferredCourses{preferredCourses} {}

bool Instructor::operator==(const Instructor& instructor) const {
    return this->m_name == instructor.m_name;
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

json Instructor::serializeToJson() const {
    json courseJson;
    for (const auto& course: m_preferredCourses) {
        courseJson.push_back(course.serializeToJson());
    }
    json availabilityJson;
    for (const auto& timeSlot: m_availability) {
        availabilityJson.push_back(timeSlot.serializeToJson());
    }
    return {
        {"m_name", m_name},
        {"m_preferredCourses", courseJson},
        {"m_availability", availabilityJson}
    };
}

Instructor Instructor::deserializeFromJson(const json& instructorJson, const std::vector<TimeSlot>& availability, const std::vector<Course>& preferredCourses) {
    Instructor deserializedInstructor = Instructor(instructorJson["m_name"].get<std::string>(), availability, preferredCourses);
    return deserializedInstructor;
}

#endif