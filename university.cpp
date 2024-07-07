#include "university.hpp"
#include <algorithm>

University::University() 
    : m_timeSlots{0, TimeSlotHash(), TimeSlotEqual()}
    , m_courses{}
    , m_instructors{} {}

void University::addCourse(const Course& course) {
    if (std::find(m_courses.begin(), m_courses.end(), course) != m_courses.end()) {
        return;
    }
    m_courses.push_back(course);
}

void University::addInstructor(const Instructor& instructor) {
    if (std::find(m_instructors.begin(), m_instructors.end(), instructor) != m_instructors.end()) {
        return;
    }
    m_instructors.push_back(instructor);
}

void University::addTimeSlot(const TimeSlot& timeSlot) {
    // if (timeSlot.getStartTime().size() != 5 || timeSlot.getEndTime().size() != 5) {
    //     std::cout << "Invalid time slot!" << std::endl;
    //     return;
    // }
    // for (int i = 0; i < timeSlot.getStartTime().size() && timeSlot.getEndTime().size(); ++i) {
    //     if (i == 2 && (timeSlot.getStartTime()[i] != ':' || timeSlot.getEndTime()[i] != ':')) {
    //         std::cout << "Invalid time slot!" << std::endl;
    //         return;
    //     }
    //     else if (i == 0 && (timeSlot.getStartTime()[i] > '2' || timeSlot.getStartTime()[i] < '0' ||
    //                         timeSlot.getEndTime()[i] > '2' || timeSlot.getEndTime()[i] < '0' ||
    //                         timeSlot.getStartTime()[i + 1] > '4' || timeSlot.getStartTime()[i + 1] < '0' ||
    //                         timeSlot.getEndTime()[i + 1] > '4' || timeSlot.getEndTime()[i + 1] < '0')) {
            
    //         std::cout << "Invalid time slot!" << std::endl;
    //         return;
    //     }
    //     else if (i == 1 && (timeSlot.getStartTime()[i] > '9' || timeSlot.getStartTime()[i] < '0' ||
    //                         timeSlot.getEndTime()[i] > '9' || timeSlot.getEndTime()[i] < '0')) {
            
    //         std::cout << "Invalid time slot!" << std::endl;
    //         return;
    //     }
    //     else if (timeSlot.getStartTime()[i] != '0' ||
    //              timeSlot.getEndTime()[i] != '0') {

    //         std::cout << "Invalid time slot!" << std::endl;
    //         return;
    //     }
        
    //     char a = timeSlot.getStartTime()[0];
    //     char b = timeSlot.getStartTime()[1];
    //     std::string startTimeHour = a + b;
    //     std::string endTimeHour = timeSlot.getEndTime()[0] + timeSlot.getEndTime()[1];
    //     int startTimeInteger = std::stoi(startTimeHour);
    //     int endTimeInteger = std::stoi(endTimeHour);
    //     if (startTimeInteger - endTimeInteger != 1) {
    //         std::cout << "Invalid time slot!" << std::endl;
    //         return;
    //     }
    // }

    // std::unordered_map<std::string, int> days = {
    //     {"Monday", 1},
    //     {"Tuesday", 2},
    //     {"Wednesday", 3},
    //     {"Thursday", 4},
    //     {"Friday", 5},
    //     {"Saturday", 6},
    //     {"Sunday", 7}
    // };

    // if (days.find(timeSlot.getDay()) == days.end()) {
    //     std::cout << "Invalid time slot!" << std::endl;
    //     return;
    // }
    
    m_timeSlots.insert(timeSlot);
}

std::size_t TimeSlotHash::operator()(const TimeSlot& s) const {
    std::size_t h1 = std::hash<std::string>()(s.getStartTime());
    std::size_t h2 = std::hash<std::string>()(s.getEndTime());
    std::size_t h3 = std::hash<std::string>()(s.getDay());

    return h1 ^ (h2 << 1) ^ (h3 << 2);
}

bool TimeSlotEqual::operator()(const TimeSlot& lhs, const TimeSlot& rhs) const {
    return lhs == rhs;
}

std::size_t CourseHash::operator()(const Course& course) const {
    std::size_t h1 = std::hash<std::string>()(course.getName());
    return h1;
}

bool CourseEqual::operator()(const Course& lhs, const Course& rhs) const {
    return lhs.getName() == rhs.getName();
}

// void University::optimizePreferredTimeSlots() {
//     std::unordered_map<TimeSlot, int, decltype(TimeSlotHash()), decltype(TimeSlotEqual())> count;
//     for (auto& course: m_courses) {
//         std::vector<TimeSlot> coursePreferredTimeSlots = course.getPreferredTimeSlots();
//         std::size_t size = coursePreferredTimeSlots.size();
//         for (int i = 0; i < size; ++i) {
//             ++count[coursePreferredTimeSlots[i]];
//         }
//     }
//     for (auto& course: m_courses) {
//         std::vector<TimeSlot> coursePreferredTimeSlots = course.getPreferredTimeSlots();
//         std::size_t size = coursePreferredTimeSlots.size();
//         //if course has 1 preferred course it can't help to optimize more
//         if (coursePreferredTimeSlots.size() == 1) {
//             continue;
//         }
//         //if has 2 and more than we can take 1 of them so that the others will have preferred too
//         for (int i = coursePreferredTimeSlots.size() - 1; i > 0; --i) {
//             if (count[coursePreferredTimeSlots[i]] > 1) {
//                 coursePreferredTimeSlots.pop_back();
//                 --count[coursePreferredTimeSlots[i]];
//             }
//             else {
//                 std::swap(coursePreferredTimeSlots[i], coursePreferredTimeSlots[0]);
//             }
//         }
//         if (size != coursePreferredTimeSlots.size()) {
//             course.setPreferredTimeSlots(coursePreferredTimeSlots);
//         }
//     }
// }

// void University::optimizePreferredCourses() {
//     std::unordered_map<Course, int, decltype(CourseHash()), decltype(CourseEqual())> count;
//     for (auto& instructor: m_instructors) {
//         std::vector<Course> insturctorPreferredCourses = instructor.getPreferredCourses();
//         std::size_t size = insturctorPreferredCourses.size();
//         for (int i = 0; i < size; ++i) {
//             ++count[insturctorPreferredCourses[i]];
//         }
//     }
//     for (auto& instructor: m_instructors) {
//         std::vector<Course> insturctorPreferredCourses = instructor.getPreferredCourses();
//         std::size_t size = insturctorPreferredCourses.size();
//         //if course has 1 preferred course it can't help to optimize more
//         if (insturctorPreferredCourses.size() == 1) {
//             continue;
//         }
//         //if has 2 and more than we can take 1 of them so that the others will have preferred too
//         for (int i = insturctorPreferredCourses.size() - 1; i > 0; --i) {
//             if (count[insturctorPreferredCourses[i]] > 1) {
//                 insturctorPreferredCourses.pop_back();
//                 --count[insturctorPreferredCourses[i]];
//             }
//             else {
//                 std::swap(insturctorPreferredCourses[i], insturctorPreferredCourses[0]);
//             }
//         }
//         if (size != insturctorPreferredCourses.size()) {
//             instructor.setPreferredCourses(insturctorPreferredCourses);
//         }
//     }
// }

std::unordered_map<TimeSlot, Instructor, decltype(TimeSlotHash()), decltype(TimeSlotEqual())> University::getIntersection() const {
    std::unordered_map<TimeSlot, Instructor, decltype(TimeSlotHash()), decltype(TimeSlotEqual())> commonTimeSlots;
    for (const auto& instructor: m_instructors) {
        std::vector<TimeSlot> availabilTimeSlots = instructor.getAvailability();
        std::size_t size = availabilTimeSlots.size();
        for (int i = 0; i < size; ++i) {
            if (m_timeSlots.find(availabilTimeSlots[i]) != m_timeSlots.end()) {
                commonTimeSlots[availabilTimeSlots[i]] = instructor;
            }
        }
    }
    return commonTimeSlots;
}

unordered_map_timetable University::schedule() {
    std::unordered_map<TimeSlot, Instructor, decltype(TimeSlotHash()), decltype(TimeSlotEqual())> commonTimeSlots = getIntersection();
    unordered_map_timetable tmpTimetable;
    unordered_map_timetable timetable;
    backtrackSchedule(0, tmpTimetable, timetable);

    bool returnFlag = false;
    for (const auto& item1: timetable) {
        for (auto item2 = commonTimeSlots.begin(); item2 != commonTimeSlots.end(); ) {
            if (item2->first == item1.second.first) {
                item2 = commonTimeSlots.erase(item2);
                if (item2 == commonTimeSlots.end()) {
                    returnFlag = true;
                    break;
                }
            }
            else {
                ++item2;
            }
        }
        if (returnFlag) {
            break;
        }
    }

    auto itr = commonTimeSlots.begin();
    for (const auto& course: m_courses) {
        if (timetable.find(course) == timetable.end()) {
            std::cout << course.getName() << std::endl;
            if (itr != commonTimeSlots.end()) {
                timetable[course] = {itr->first, itr->second};
                ++itr;
            }
        }
    }
    return timetable;
}

bool University::backtrackSchedule(int courseIndex, unordered_map_timetable& tmpTimetable, unordered_map_timetable& timetable) {
    if (courseIndex == m_courses.size()) {
        if (tmpTimetable.size() > timetable.size()) {
            timetable = tmpTimetable;
        }
        return timetable.size() == tmpTimetable.size(); // All courses are scheduled
    }

    bool foundCompleteSchedule = false;
    Course& course = m_courses[courseIndex];
    for (const auto& timeSlot : course.getPreferredTimeSlots()) {
        for (auto& instructor : m_instructors) {
            if (instructor.isAvailable(timeSlot) && instructor.prefersCourse(course) && !isTimeSlotAssigned(timeSlot)) {
                assignCourseToInstructor(course, instructor, timeSlot, tmpTimetable);

                if (backtrackSchedule(courseIndex + 1, tmpTimetable, timetable)) {
                    foundCompleteSchedule = true;
                }

                unassignCourseFromInstructor(course, instructor, timeSlot, tmpTimetable);
            }
        }
    }

    if (tmpTimetable.size() > timetable.size()) {
        timetable = tmpTimetable;
    }

    return foundCompleteSchedule; // No valid schedule found
}

void University::assignCourseToInstructor(Course& course, Instructor& instructor, const TimeSlot& timeSlot, unordered_map_timetable& timetable) {
    instructor.pushTimeSlot(timeSlot);
    timetable[course] = {timeSlot, instructor};
}

void University::unassignCourseFromInstructor(Course& course, Instructor& instructor, const TimeSlot& timeSlot, unordered_map_timetable& timetable) {
    instructor.popTimeSlot();
    timetable.erase(course);
}

bool University::isTimeSlotAssigned(const TimeSlot& timeSlot) const {
    for (const auto& instructor : m_instructors) {
        for (const auto& assignedSlot : instructor.getAssignedTimeSlots()) {
            if (assignedSlot == timeSlot) {
                return true;
            }
        }
    }
    return false;
}
