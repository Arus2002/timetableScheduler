#include <iostream>
#include <string>
#include "dependencies/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class TimeSlot {
public:
    TimeSlot() = default;
    TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime);
    ~TimeSlot() = default;
    bool operator==(const TimeSlot& other) const;
    void displayInfo() const;
    std::string getStartTime() const;
    std::string getEndTime() const;
    std::string getDay() const;

public: //json functions
    json serializeToJson() const;
    static TimeSlot deserializeFromJson(const json& timeSlotJson);

private:
    void timeSlotChecker() const;

private:
    std::string m_day;
    std::string m_startTime;
    std::string m_endTime;
};

struct TimeSlotHash {
    std::size_t operator()(const TimeSlot& s) const;
};

struct TimeSlotEqual {
    bool operator()(const TimeSlot& lhs, const TimeSlot& rhs) const;
};