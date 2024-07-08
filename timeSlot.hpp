#include <iostream>
#include <string>

class TimeSlot {
public:
    TimeSlot() = default;
    TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime);
    ~TimeSlot() = default;
    void displayInfo() const;
    std::string getStartTime() const;
    std::string getEndTime() const;
    std::string getDay() const;
    bool operator==(const TimeSlot& other) const;
    void timeSlotChecker() const;

private:
    std::string m_day;
    std::string m_startTime;
    std::string m_endTime;
};