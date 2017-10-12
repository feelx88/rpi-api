project(rpi-api)
cmake_minimum_required(VERSION 3.5)
add_subdirectory(pistache)

set(SRC
    main.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/pistache/include)

add_executable(api ${SRC})
target_link_libraries(api pthread pistache)
