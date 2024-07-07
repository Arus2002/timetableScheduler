#include "course.hpp"

class Instructor {
public:
    Instructor(const std::string& name, const std::vector<TimeSlot>& availability, const std::vector<Course>& preferredCourses);
    ~Instructor() = default;
    Instructor() = default;
    void displayInfo() const;
    std::vector<TimeSlot> getAvailability() const;
    std::vector<Course> getPreferredCourses() const;
    std::string getName() const;
    void setPreferredCourses(const std::vector<Course>& courses);
    bool isAvailable(const TimeSlot& timeSlot) const;
    bool prefersCourse(const Course& course) const;
    std::vector<TimeSlot> getAssignedTimeSlots() const;
    void pushTimeSlot(const TimeSlot& timeSlot);
    void popTimeSlot();
    bool operator==(const Instructor& instructor) const;

private:
    std::string m_name;
    std::vector<TimeSlot> m_availability;
    std::vector<Course> m_preferredCourses;
    std::vector<TimeSlot> m_assignedTimeSlots;
};