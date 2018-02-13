cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_definitions(-Wall -Wno-unknown-pragmas)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/../cmake")

find_package(ODB REQUIRED COMPONENTS sqlite)
include_directories(${ODB_INCLUDE_DIRS})
include(${ODB_USE_FILE})

include_directories(include)
include_directories(${ODB_COMPILE_OUTPUT_DIR})

set(OBJ_HEADER
    include/Deployment.hpp
    include/Measurement.hpp
    include/SensorInterpretation.hpp
    include/SensorNode.hpp
)


odb_compile(ODB_SRC
    FILES ${OBJ_HEADER}
    INCLUDE include
    PROJECT_INCLUDE ${PROJECT_SOURCE_DIR}/include
    DB sqlite GENERATE_QUERY GENERATE_SESSION GENERATE_SCHEMA STANDARD c++11)


set(SRC
    src/Deployment.cpp
    src/Storage.cpp
    src/main.cpp
)

add_executable(test_model ${SRC} ${ODB_SRC})
target_link_libraries(test_model ${ODB_LIBRARIES})
