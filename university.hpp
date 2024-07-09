#ifndef UNIVERSITY_HPP
#define UNIVERSITY_HPP

#include "instructor.hpp"
#include <unordered_map>
#include <unordered_set>

using unordered_map_timetable = std::unordered_map<Course, std::pair<TimeSlot, Instructor>, decltype(CourseHash()), decltype(CourseEqual())>;

class University {
public:
    University();
    ~University() = default;
    void addCourse(const Course& cource);
    void addInstructor(const Instructor& instructor);
    void addTimeSlot(const TimeSlot& timeSlot);
    unordered_map_timetable schedule();

public: //json functions
    std::string saveState() const;
    void loadState(const std::string& filename);

private:
    std::unordered_map<TimeSlot, Instructor, decltype(TimeSlotHash()), decltype(TimeSlotEqual())> getIntersection() const;
    bool backtrackSchedule(std::size_t courseIndex, unordered_map_timetable& timetable, unordered_map_timetable& tmpTimetable, const std::unordered_map<TimeSlot, Instructor, decltype(TimeSlotHash()), decltype(TimeSlotEqual())>& commonTimeSlots);
    void assignCourseToInstructor(Course& course, Instructor& instructor, const TimeSlot& timeSlot, unordered_map_timetable& timetable);
    void unassignCourseFromInstructor(Course& course, Instructor& instructor, const TimeSlot& timeSlot, unordered_map_timetable& timetable);
    bool isTimeSlotAssigned(const TimeSlot& timeSlot) const;
    void optimizeCourses();
    
private:
    std::unordered_set<TimeSlot, decltype(TimeSlotHash()), decltype(TimeSlotEqual())> m_timeSlots;
    std::vector<Course> m_courses;
    std::vector<Instructor> m_instructors;
    std::unordered_set<TimeSlot, decltype(TimeSlotHash()), decltype(TimeSlotEqual())> m_assignedTimeSlots;
};

#endif