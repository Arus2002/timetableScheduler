#include "university.hpp"
#include <algorithm>
#include <fstream>

University::University() 
    : m_timeSlots{0, TimeSlotHash(), TimeSlotEqual()}
    , m_courses{}
    , m_instructors{} {}

void University::addCourse(const Course& course) {
    if (std::find(m_courses.begin(), m_courses.end(), course) != m_courses.end()) {
        std::cout << "This course has been already pushed!" << course.getName() << std::endl;
        return;
    }
    m_courses.push_back(course);
}

void University::addInstructor(const Instructor& instructor) {
    if (std::find(m_instructors.begin(), m_instructors.end(), instructor) != m_instructors.end()) {
        std::cout << "This instructor has been already pushed!" << instructor.getName() << std::endl;
        return;
    }
    m_instructors.push_back(instructor);
}

void University::addTimeSlot(const TimeSlot& timeSlot) {
    if (m_timeSlots.find(timeSlot) != m_timeSlots.end()) {
        std::cout << "This time slot has been already pushed!";
        timeSlot.displayInfo();
        return;
    }
    m_timeSlots.insert(timeSlot);
}

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
    std::size_t index = 0;
    optimizeCourses();
    backtrackSchedule(index , tmpTimetable, timetable, commonTimeSlots);

    for (const auto& item1: timetable) {
        for (auto item2 = commonTimeSlots.begin(); item2 != commonTimeSlots.end(); ) {
            if (item2->first == item1.second.first) {
                item2 = commonTimeSlots.erase(item2);
            }
            else {
                ++item2;
            }
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

bool University::backtrackSchedule(std::size_t courseIndex, unordered_map_timetable& tmpTimetable, unordered_map_timetable& timetable, const std::unordered_map<TimeSlot, Instructor, decltype(TimeSlotHash()), decltype(TimeSlotEqual())>& commonTimeSlots) {
    if (courseIndex == m_courses.size()) {
        if (tmpTimetable.size() > timetable.size()) {
            timetable = tmpTimetable;
        }
        return timetable.size() == tmpTimetable.size();
    }

    bool foundCompleteSchedule = false;
    Course& course = m_courses[courseIndex];
    for (const auto& timeSlot : course.getPreferredTimeSlots()) {
        for (auto& instructor : m_instructors) {
            if (instructor.isAvailable(timeSlot) && instructor.prefersCourse(course) && !isTimeSlotAssigned(timeSlot) && m_timeSlots.find(timeSlot) != m_timeSlots.end()) {
                assignCourseToInstructor(course, instructor, timeSlot, tmpTimetable);

                if (backtrackSchedule(courseIndex + 1, tmpTimetable, timetable, commonTimeSlots)) {
                    foundCompleteSchedule = true;
                }

                unassignCourseFromInstructor(course, instructor, timeSlot, tmpTimetable);
            }
        }
    }
    if (!foundCompleteSchedule) {
        for (const auto& timeSlot : course.getPreferredTimeSlots()) {
            for (auto& instructor : m_instructors) {
                if (instructor.isAvailable(timeSlot) && !isTimeSlotAssigned(timeSlot) && m_timeSlots.find(timeSlot) != m_timeSlots.end()) {
                    assignCourseToInstructor(course
                    , instructor, timeSlot, tmpTimetable);

                    if (backtrackSchedule(courseIndex + 1, tmpTimetable, timetable, commonTimeSlots)) {
                        foundCompleteSchedule = true;
                    }

                    unassignCourseFromInstructor(course, instructor, timeSlot, tmpTimetable);
                }
            }
        }
    }
    if (!foundCompleteSchedule) {
        for (const auto& timeSlot : commonTimeSlots) {
            for (auto& instructor : m_instructors) {
                if (instructor.isAvailable(timeSlot.first) && instructor.prefersCourse(course) && !isTimeSlotAssigned(timeSlot.first)) {
                    assignCourseToInstructor(course, instructor, timeSlot.first, tmpTimetable);

                    if (backtrackSchedule(courseIndex + 1, tmpTimetable, timetable, commonTimeSlots)) {
                        foundCompleteSchedule = true;
                    }

                    unassignCourseFromInstructor(course, instructor, timeSlot.first, tmpTimetable);
                }
            }
        }
    }

    if (tmpTimetable.size() > timetable.size()) {
        timetable = tmpTimetable;
    }

    return foundCompleteSchedule;
}

void University::assignCourseToInstructor(Course& course, Instructor& instructor, const TimeSlot& timeSlot, unordered_map_timetable& timetable) {
    m_assignedTimeSlots.insert(timeSlot);
    timetable[course] = {timeSlot, instructor};
}

void University::unassignCourseFromInstructor(Course& course, Instructor& instructor, const TimeSlot& timeSlot, unordered_map_timetable& timetable) {
    m_assignedTimeSlots.erase(timeSlot);
    timetable.erase(course);
}

bool University::isTimeSlotAssigned(const TimeSlot& timeSlot) const {
    for (const auto& assignedSlot: m_assignedTimeSlots) {
        if (assignedSlot == timeSlot) {
            return true;
        }
    }
    return false;
}

void University::optimizeCourses() {
    std::sort(m_courses.begin(), m_courses.end(), [](const Course& c1, const Course& c2) {
        return c1.getPreferredTimeSlots().size() < c2.getPreferredTimeSlots().size();});
}

std::string University::saveState() const {
    json universityJson;
        
    for (const auto& course : m_courses) {
        universityJson["m_courses"].push_back(course.serializeToJson());
    }
    for (const auto& instructor : m_instructors) {
        universityJson["m_instructors"].push_back(instructor.serializeToJson());
    }
    for (const auto& timeSlot : m_timeSlots) {
        universityJson["m_timeSlots"].push_back(timeSlot.serializeToJson());
    }
    
    std::string filename;
    std::cout << "Please input filenmae" << std::endl;
    std::cin >> filename;
    std::ofstream file(filename);
    file << universityJson.dump(4);
    file.close();
    return filename;
}

void University::loadState(const std::string& filename) {
    m_instructors.clear();
    m_timeSlots.clear();
    m_courses.clear();
    std::ifstream file(filename);
    json universityJson;
    file >> universityJson;
    file.close();
    
    for (const auto& courseJson : universityJson["m_courses"]) {
        std::vector<TimeSlot> timeSlots;
        for (const auto& timeSlotJson : courseJson["m_preferredTimeSlots"]) {
            timeSlots.push_back(TimeSlot::deserializeFromJson(timeSlotJson));
        }
        m_courses.push_back(Course::deserializeFromJson(courseJson, timeSlots));
    }

    for (const auto& instructorJson : universityJson["m_instructors"]) {
        std::vector<TimeSlot> availability;
        for (const auto& timeSlotJson : instructorJson["m_availability"]) {
            availability.push_back(TimeSlot::deserializeFromJson(timeSlotJson));
        }
        
        std::vector<Course> preferredCourses;
        for (const auto& courseJson : instructorJson["m_preferredCourses"]) {
            std::vector<TimeSlot> timeSlots;
            for (const auto& timeSlotJson : courseJson["m_preferredTimeSlots"]) {
                timeSlots.push_back(TimeSlot::deserializeFromJson(timeSlotJson));
            }
            preferredCourses.push_back(Course::deserializeFromJson(courseJson, timeSlots));
        }
        m_instructors.push_back(Instructor::deserializeFromJson(instructorJson, availability, preferredCourses));
    }
    
    for (const auto& timeSlotJson : universityJson["m_timeSlots"]) {
        TimeSlot deserializedTimeSlot = TimeSlot::deserializeFromJson(timeSlotJson);
        m_timeSlots.insert(deserializedTimeSlot);
    }
}