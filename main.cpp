#include "university.hpp"

int main() {
    //University university;

    TimeSlot timeSlot1("Monday", "09:00", "10:30");
    TimeSlot timeSlot2("Monday", "11:00", "12:30");
    TimeSlot timeSlot3("Wednesday", "09:00", "10:30");
    TimeSlot timeSlot4("Wednesday", "11:00", "12:30");
    TimeSlot timeSlot5("Friday", "11:30", "13:00");

    Course course1("Math", {timeSlot1});
    Course course2("Physics", {timeSlot2});
    Course course3("Chemistry", {timeSlot3});
    Course course4("Biology", {timeSlot4});
    Course course5("History", {timeSlot5});

    Instructor instructor1("Alice", {timeSlot1, timeSlot2}, {course1, course2});
    Instructor instructor2("Bob", {timeSlot3, timeSlot4}, {course3, course4});
    Instructor instructor3("Carol", {timeSlot3, timeSlot5}, {course1, course5});

    University university;
    university.addCourse(course1);
    university.addCourse(course2);
    university.addCourse(course3);
    university.addCourse(course4);
    university.addCourse(course5);
    university.addInstructor(instructor2);
    university.addInstructor(instructor1);
    university.addInstructor(instructor3);
    university.addTimeSlot(timeSlot1);
    university.addTimeSlot(timeSlot2);
    university.addTimeSlot(timeSlot3);
    university.addTimeSlot(timeSlot4);
    university.addTimeSlot(timeSlot5);
    //university.loadState("test_1");

    std::unordered_map<Course, std::pair<TimeSlot, Instructor>, decltype(CourseHash()), decltype(CourseEqual())> timetable = university.schedule();
    if (!timetable.empty()) {
        std::cout << "Created successfully!" << std::endl;
        for (const auto& item : timetable) {
            std::cout << item.first.getName() << " scheduled with " << item.second.second.getName() 
                << " on " << item.second.first.getDay() << " from " << item.second.first.getStartTime() 
                << " to " << item.second.first.getEndTime() << std::endl;
        }
    } 
    else {
        std::cout << "Failed!" << std::endl;
    }
}
