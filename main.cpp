#include "university.hpp"

int main() {
    University university;

    //Tests in json files
    university.loadState("test_1");
    // university.loadState("test_2");
    // university.loadState("test_3");
    // university.loadState("test_4");
    // university.loadState("test_5");
    // university.loadState("test_6");
    // university.loadState("test_7");
    // university.loadState("test_8");
    // university.loadState("test_9");

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
