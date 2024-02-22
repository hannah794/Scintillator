cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Scintillator)

set(CMAKE_CXX_STANDARD 17)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(scintillator main.cc ${sources} ${headers})
target_link_libraries(scintillator ${Geant4_LIBRARIES})
