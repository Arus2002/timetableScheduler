#include "university.hpp"

int main() {
   // Create some time slots
    TimeSlot slot1("Monday", "09:00", "10:00");
    TimeSlot slot2("Monday", "10:00", "11:00");
    TimeSlot slot3("Tuesday", "09:00", "10:00");

    // Create some courses
    Course course1("Math", {slot1, slot2});
    Course course2("Physics", {slot3});
    Course course3("Chemistry", {slot1, slot3});

    // Create some instructors
    Instructor instructor1("Dr. Smith", {slot1, slot2}, {course1, course2});
    Instructor instructor2("Dr. Johnson", {slot2, slot3}, {course2, course3});

    // Create a university and add the entities
    University university;
    university.addCourse(course1);
    university.addCourse(course2);
    university.addCourse(course3);

    university.addInstructor(instructor1);
    university.addInstructor(instructor2);

    university.addTimeSlot(slot1);
    university.addTimeSlot(slot2);
    university.addTimeSlot(slot3);

    std::unordered_map<Course, std::pair<TimeSlot, Instructor>, decltype(CourseHash()), decltype(CourseEqual())> timetable = university.schedule();
    if (!timetable.empty()) {
            std::cout << "Schedule created successfully!" << std::endl;
            for (const auto& entry : timetable) {
                std::cout << entry.first.getName() << " scheduled with " << entry.second.second.getName() 
                        << " on " << entry.second.first.getDay() << " from " << entry.second.first.getStartTime() 
                        << " to " << entry.second.first.getEndTime() << std::endl;
            }
        } else {
            std::cout << "Failed to create a schedule." << std::endl;
        }


    return 0;
}

//insturctorinel petqa pahem
//ete unem hatvox jamer instructori hamar (09:00 - 10:30 ev 09:30-11:00 lara lini menak vory vor vercnum enq iranic 1 u kes jam hetoyva jamy) petqa vercnel ayn vory ka time_sloteri listum 