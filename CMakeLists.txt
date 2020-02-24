project(fcalc LANGUAGES CXX)

add_library(calclib STATIC src/calclib.cpp include/calclib/calclib.hpp)
target_include_directories(calclib PUBLIC include)

add_executable(fcalc src/calc.cpp)
target_link_libraries(fcalc PUBLIC calclib)

add_executable(fcalc_profiling src/profiling.cpp)
target_link_libraries(fcalc_profiling PUBLIC calclib)
