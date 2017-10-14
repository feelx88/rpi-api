include(ExternalProject)

project(rpi-api)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS -std=c++11)

ExternalProject_Add(
  pistache
  PREFIX "${CMAKE_SOURCE_DIR}/vendor"
  GIT_REPOSITORY "https://github.com/oktal/pistache.git"
  GIT_TAG "master"
  INSTALL_COMMAND ""
)

ExternalProject_Add(
  jwt-cpp
  PREFIX "${CMAKE_SOURCE_DIR}/vendor"
  GIT_REPOSITORY "https://github.com/pokowaka/jwt-cpp.git"
  GIT_TAG "modern_json"
  INSTALL_COMMAND ""
)

ExternalProject_Add(
  mongocxx
  PREFIX "${CMAKE_SOURCE_DIR}/vendor"
  GIT_REPOSITORY "https://github.com/mongodb/mongo-cxx-driver.git"
  GIT_TAG "releases/stable"
  INSTALL_COMMAND ""
)

set(SRC
    main.cpp
)

set(ASSETS
  .gitignore
  .gitmodules
  LICENSE
  README.md
)
add_custom_target(assets SOURCES ${ASSETS})

include_directories(${CMAKE_SOURCE_DIR}/vendor/src/pistache/include)

add_executable(api ${SRC})
add_dependencies(api pistache jwt-cpp)
target_link_libraries(
  api
  pthread
  ${CMAKE_SOURCE_DIR}/vendor/src/pistache-build/src/libpistache.a
)
