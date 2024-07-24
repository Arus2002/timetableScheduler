#include "university.hpp"

int main() {
    University university;
    university.loadState("tests/test_1");
    //university.loadState("tests/test_2");
    //university.loadState("tests/test_3");
    //university.loadState("tests/test_4");
    //university.loadState("tests/test_5");
    //university.loadState("tests/test_6");
    //university.loadState("tests/test_7");
    //university.loadState("tests/test_8");
    //university.loadState("tests/test_9");

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
