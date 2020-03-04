cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(fcalc LANGUAGES CXX)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

add_library(calclib STATIC src/calclib.cpp include/calclib/calclib.hpp)
target_include_directories(calclib PUBLIC include)

add_executable(fcalc
        src/calc.cpp
        src/qt/mainwindow.cpp
        src/qt/mainwindow.h
        src/qt/mainwindow.ui
        )
target_link_libraries(fcalc PUBLIC calclib)

find_package(Qt5Widgets CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

add_executable(fcalc_profiling src/profiling.cpp)
target_link_libraries(fcalc_profiling PUBLIC calclib)
