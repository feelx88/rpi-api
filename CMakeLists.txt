project(rpi-api)
cmake_minimum_required(VERSION 3.5)


SET(SRC
    main.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/pistache/include)

add_executable(api ${SRC})
target_link_libraries(api pthread ${CMAKE_SOURCE_DIR}/pistache/build/src/libpistache.a)
