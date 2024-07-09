#include "university.hpp"

int main() {
    TimeSlot timeSlot1("Monday", "09:00", "10:00");
    TimeSlot timeSlot2("Monday", "11:00", "12:00");
    TimeSlot timeSlot3("Wednesday", "09:00", "10:00");
    TimeSlot timeSlot4("Wednesday", "11:00", "12:00");
    TimeSlot timeSlot5("Friday", "12:00", "13:00");

    Course course1("Math", {timeSlot3, timeSlot1, timeSlot4});
    Course course2("Physics", {timeSlot2, timeSlot4});
    Course course3("Chemistry", {timeSlot1, timeSlot4});
    Course course4("Biology", {timeSlot2, timeSlot3});
    Course course5("History", {timeSlot3});

    Instructor instructor1("Alice", {timeSlot1, timeSlot2, timeSlot3}, {course1, course2});
    Instructor instructor2("Bob", {timeSlot1, timeSlot2, timeSlot4, timeSlot5}, {course2, course3, course5});
    Instructor instructor3("Carol", {timeSlot3, timeSlot4}, {course4});

    University university;
    university.addCourse(course2);
    university.addCourse(course3);
    university.addCourse(course4);
    university.addCourse(course1);
    university.addCourse(course5);
    university.addInstructor(instructor1);
    university.addInstructor(instructor2);
    university.addInstructor(instructor3);
    university.addTimeSlot(timeSlot1);
    university.addTimeSlot(timeSlot2);
    university.addTimeSlot(timeSlot3);
    university.addTimeSlot(timeSlot4);
    university.addTimeSlot(timeSlot5);
    
    std::unordered_map<Course, std::pair<TimeSlot, Instructor>, decltype(CourseHash()), decltype(CourseEqual())> timetable = university.schedule();
    if (!timetable.empty()) {
        std::cout << "Created successfully!" << std::endl;
        for (const auto& entry : timetable) {
            std::cout << entry.first.getName() << " scheduled with " << entry.second.second.getName() 
                    << " on " << entry.second.first.getDay() << " from " << entry.second.first.getStartTime() 
                    << " to " << entry.second.first.getEndTime() << std::endl;
        }
    } 
    else {
        std::cout << "Failed!" << std::endl;
    }
    std::string filename = university.saveState();

    return 0;
}
