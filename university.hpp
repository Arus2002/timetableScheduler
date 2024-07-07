#include "instructor.hpp"
#include <unordered_map>
#include <unordered_set>

struct TimeSlotHash {
    std::size_t operator()(const TimeSlot& s) const;
};

struct TimeSlotEqual {
    bool operator()(const TimeSlot& lhs, const TimeSlot& rhs) const;
};

struct CourseHash {
    std::size_t operator()(const Course& course) const;
};

struct CourseEqual {
    bool operator()(const Course& lhs, const Course& rhs) const;
};

using unordered_map_timetable = std::unordered_map<Course, std::pair<TimeSlot, Instructor>, decltype(CourseHash()), decltype(CourseEqual())>;

class University {
public:
    University();
    ~University() = default;
    void addCourse(const Course& cource);
    void addInstructor(const Instructor& instructor);
    void addTimeSlot(const TimeSlot& timeSlot);
    // void saveState() const;
    // void loadState() const;
    unordered_map_timetable schedule();

private:
    std::unordered_map<TimeSlot, Instructor, decltype(TimeSlotHash()), decltype(TimeSlotEqual())> getIntersection() const;
    bool backtrackSchedule(int courseIndex, unordered_map_timetable& timetable, unordered_map_timetable& tmpTimetable);
    void assignCourseToInstructor(Course& course, Instructor& instructor, const TimeSlot& timeSlot, unordered_map_timetable& timetable);
    void unassignCourseFromInstructor(Course& course, Instructor& instructor, const TimeSlot& timeSlot, unordered_map_timetable& timetable);
    bool isTimeSlotAssigned(const TimeSlot& timeSlot) const;
    void optimizePreferredTimeSlots();
    void optimizePreferredCourses();
    
private:
    std::unordered_set<TimeSlot, decltype(TimeSlotHash()), decltype(TimeSlotEqual())> m_timeSlots;
    std::vector<Course> m_courses;
    std::vector<Instructor> m_instructors;
};