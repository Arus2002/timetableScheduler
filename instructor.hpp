#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP

#include "course.hpp"

class Instructor {
public:
    Instructor(const std::string& name, const std::vector<TimeSlot>& availability, const std::vector<Course>& preferredCourses);
    ~Instructor() = default;
    Instructor() = default;
    bool operator==(const Instructor& instructor) const;
    void displayInfo() const;
    std::vector<TimeSlot> getAvailability() const;
    std::vector<Course> getPreferredCourses() const;
    std::string getName() const;
    bool isAvailable(const TimeSlot& timeSlot) const;
    bool prefersCourse(const Course& course) const;

public: //json functions
    json serializeToJson() const;
    static Instructor deserializeFromJson(const json& instructorJson, const std::vector<TimeSlot>& availability, const std::vector<Course>& preferredCourses);

private:
    std::string m_name;
    std::vector<TimeSlot> m_availability;
    std::vector<Course> m_preferredCourses;
};

#endif