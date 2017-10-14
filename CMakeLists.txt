include(ExternalProject)

project(rpi-api)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS -std=c++11)


set(EP_PREFIX "${CMAKE_SOURCE_DIR}/vendor")
ExternalProject_Add(
  pistache
  GIT_REPOSITORY "https://github.com/oktal/pistache.git"
  GIT_TAG "master"
  INSTALL_COMMAND ""
)

ExternalProject_Add(
  jwt-cpp
  GIT_REPOSITORY "https://github.com/pokowaka/jwt-cpp.git"
  GIT_TAG "modern_json"
  INSTALL_COMMAND ""
)

ExternalProject_Add(
  mongocxx
  GIT_REPOSITORY "https://github.com/mongodb/mongo-cxx-driver.git"
  GIT_TAG "releases/stable"
  INSTALL_COMMAND ""
)

ExternalProject_Add(
  wiringpi
  LIST_SEPARATOR "#"
  GIT_REPOSITORY "git://git.drogon.net/wiringPi"
  GIT_TAG "master"
  CONFIGURE_COMMAND ""
  BINARY_DIR "${EP_PREFIX}/src/wiringpi/wiringPi"
  BUILD_COMMAND make static
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
  ${CMAKE_SOURCE_DIR}/vendor/src/mongocxx-build/src/bsoncxx/libbsoncxx.a
  ${CMAKE_SOURCE_DIR}/vendor/src/mongocxx-build/src/mongocxx/libmongocxx.a
  ${CMAKE_SOURCE_DIR}/vendor/src/wiringpi/wiringPi/libwiringPi.a
)
