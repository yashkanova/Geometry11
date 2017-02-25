
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Geometry)


set(CMAKE_PREFIX_PATH /home/student/geant4/geant4-install)

option(WITH_GEANT4_UIVIS "Build project with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(Geometry main.cc ${sources} ${headers})
target_link_libraries(Geometry ${Geant4_LIBRARIES})



set(EXAMPLEB1_SCRIPTS
  init_vis.mac
  vis.mac
  )

foreach(_script ${EXAMPLEB1_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


install(TARGETS Geometry DESTINATION bin)


