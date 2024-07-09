#include "timeSlot.hpp"
#include <vector>

class Course {
public:
    Course(const std::string& courseName, const std::vector<TimeSlot>& preferrredTimeSlots);
    ~Course() = default;
    Course() = default;
    bool operator==(const Course& course) const;
    void displayInfo() const;
    std::string getName() const;
    std::vector<TimeSlot> getPreferredTimeSlots() const;
    
public: //json functions
    json serializeToJson() const;
    static Course deserializeFromJson(const json& courseJson, const std::vector<TimeSlot>& timeSlots);

private:
    std::string m_courseName;
    std::vector<TimeSlot> m_preferredTimeSlots;
};

struct CourseHash {
    std::size_t operator()(const Course& course) const;
};

struct CourseEqual {
    bool operator()(const Course& lhs, const Course& rhs) const;
};