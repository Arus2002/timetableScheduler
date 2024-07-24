cmake_minimum_required(VERSION 3.16)

project(UniversityTimetableSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(UniversityTimetableSystem
    course.cpp
    instructor.cpp
    timeSlot.cpp
    university.cpp
    main.cpp
)

target_include_directories(UniversityTimetableSystem
    PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies
)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(DEST_DIR "${CMAKE_BINARY_DIR}")

foreach(test_file IN ITEMS tests/test_1 tests/test_2 tests/test_3 tests/test_4 tests/test_5 tests/test_6 tests/test_7 tests/test_8 tests/test_9)
    add_custom_command(TARGET UniversityTimetableSystem POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${SOURCE_DIR}/${tests}/${test_file} ${DEST_DIR}/${test_file}
    )
endforeach()
