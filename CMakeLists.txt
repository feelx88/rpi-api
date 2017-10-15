include(ExternalProject)

project(rpi-api)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS -std=c++11)

set_directory_properties(PROPERTIES EP_PREFIX "${CMAKE_SOURCE_DIR}/vendor")
ExternalProject_Add(
  pistache
  GIT_REPOSITORY "https://github.com/oktal/pistache.git"
  GIT_TAG "master"
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
)

ExternalProject_Add(
  jwt-cpp
  GIT_REPOSITORY "https://github.com/pokowaka/jwt-cpp.git"
  GIT_TAG "modern_json"
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
)

ExternalProject_Add(
  mongocxx
  GIT_REPOSITORY "https://github.com/mongodb/mongo-cxx-driver.git"
  GIT_TAG "releases/stable"
  UPDATE_COMMAND ""
  CMAKE_ARGS -DBSONCXX_POLY_USE_BOOST=1 -DBSONCXX_POLY_USE_MNMLSTC=0
  INSTALL_COMMAND ""
)

ExternalProject_Add(
  wiringpi
  LIST_SEPARATOR "#"
  GIT_REPOSITORY "git://git.drogon.net/wiringPi"
  GIT_TAG "master"
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BINARY_DIR "${CMAKE_SOURCE_DIR}/vendor/src/wiringpi/wiringPi"
  BUILD_COMMAND make static
  INSTALL_COMMAND ""
)

ExternalProject_Add(
  jsoncpp
  GIT_REPOSITORY "https://github.com/nlohmann/json.git"
  GIT_TAG "master"
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
)

set(SRC
  src/main.cpp
  src/handler/auth.cpp
)

set(HEADERS
  include/router.hpp
  include/handler/auth.hpp
)

set(ASSETS
  .gitignore
  LICENSE
  README.md
)
add_custom_target(assets SOURCES ${ASSETS})

include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/src/pistache/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/src/mongocxx/src)
include_directories(${CMAKE_SOURCE_DIR}/vendor/src/mongocxx-build/src)
include_directories(${CMAKE_SOURCE_DIR}/vendor/src/jsoncpp/src)
include_directories(${MONGOC_INCLUDE_DIRS})

find_package (libmongoc-1.0 1.7 REQUIRED)

add_executable(api ${SRC} ${HEADERS})
add_dependencies(api pistache jwt-cpp mongocxx wiringpi jsoncpp)
target_link_libraries(
  api
  pthread
  ${MONGOC_LIBRARIES}
  ${CMAKE_SOURCE_DIR}/vendor/src/pistache-build/src/libpistache.a
  ${CMAKE_SOURCE_DIR}/vendor/src/mongocxx-build/src/bsoncxx/libbsoncxx.a
  ${CMAKE_SOURCE_DIR}/vendor/src/mongocxx-build/src/mongocxx/libmongocxx.a
  ${CMAKE_SOURCE_DIR}/vendor/src/wiringpi/wiringPi/libwiringPi.a
)
