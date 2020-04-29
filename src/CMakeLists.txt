cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(fitutubies-calculator LANGUAGES CXX)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
		${CMAKE_CURRENT_BINARY_DIR}/googletest-build
		EXCLUDE_FROM_ALL)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Add resource files
set(CMAKE_AUTORCC ON)

add_library(calclib STATIC main/calclib.cpp include/calclib/calclib.hpp)
target_include_directories(calclib PUBLIC include)
target_include_directories(calclib PRIVATE lib/lexertk)

add_executable(fitutubies-calculator
		main/calc.cpp
		main/qt/mainwindow.cpp
		main/qt/mainwindow.h
		main/qt/mainwindow.ui
		main/qt/manualwindow.cpp
		main/qt/manualwindow.h
		main/qt/manualwindow.ui
		main/qt/resources/resources.qrc
        )

target_link_libraries(fitutubies-calculator PUBLIC calclib)
find_package(Qt5 COMPONENTS Widgets WebEngineWidgets)
target_link_libraries(fitutubies-calculator PRIVATE Qt5::Widgets Qt5::WebEngineWidgets)

add_executable(calclib_test
		test/calclib_test.cpp
)
target_link_libraries(calclib_test calclib)
target_link_libraries(calclib_test gtest_main)

add_executable(fitutubies-calculator_profiling main/profiling.cpp)
target_link_libraries(fitutubies-calculator_profiling PUBLIC calclib)
