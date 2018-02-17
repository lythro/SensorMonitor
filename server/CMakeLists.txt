
cmake_minimum_required(VERSION 2.6)

include_directories(3rdparty/rcswitch-pi)
add_executable(server src/main.cpp 3rdparty/rcswitch-pi/RCSwitch.cpp)
target_link_libraries(server wiringPi)

