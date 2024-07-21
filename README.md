## University Timetable Scheduler

This assignment aims to design and implement a program that schedules courses for a university while assigning instructors to each course based on their availability and expertise. 
This will involve creating classes to represent courses and instructors, as well as implementing an algorithm to schedule a timetable.

## Constraints

### Hard Constraints

- Each course must be scheduled exactly once in an available time slot and assigned to an instructor.
- An instructor can only be assigned to a course if they are available during the corresponding time slot.
- An instructor cannot be scheduled to teach more than one course in the same time slot.

### Soft Constraints

- Courses should be scheduled in preferred time slots if possible.
- Instructors should be assigned to their preferred courses if possible.

In this university, the lessons start and end times are fixed with an interval of exactly 1 hour. Availability of instructors and time slots for courses can only be in full-hour increments (e.g., 9:00-10:00, 10:00-11:00).

## Approach for Scheduling

First we get all time slots that we have both in time slots of university and in instructor's availabilities, 
than we recoursively call function which at first if it is possible take course with both constraints, if not take the course with at least one constraint. 
Only after these calls if it can't find any possible way it assign course to some free time slot.

## Installation

To install and set up the Timetable Scheduler project, follow these steps:

```bash
# Clone the repository
git clone https://github.com/Arus2002/timetableScheduler

# Navigate to the project directory
cd timetableScheduler

# Compile all C++ files
g++ *.cpp -o main

# Usage
After compiling the project, you can run the executable to start the scheduling process: 
./main

## Testing
# Open main.cpp and uncomment the desired test lines 

# Recompile the program
g++ *.cpp -o main

# Run the program
./main

Project Link: https://github.com/Arus2002/timetableScheduler
