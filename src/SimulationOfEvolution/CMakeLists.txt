cmake_minimum_required(VERSION 3.22.0)


include(cmake/vcpkg.cmake)

project(SimulationOfEvolution VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_HOST_WIN32)
  set(OBJECT_PATH_MAX 260)
  set(OBJECT_NAME_MAX 255)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME} "Main.cpp" "Neurons.h" "Neurons.cpp" "utilites.h" "Creature.h" "Creature.cpp" "Environment.h" "Environment.cpp" "QtGraphics.cpp" "QtGraphics.h") 
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    file(GLOB PLUGIN_FILES "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/Debug/QT6/plugins/platforms/*")
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    file(GLOB PLUGIN_FILES "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/QT6/plugins/platforms/*")
endif()
if(WIN32)
    file( MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/platforms" )
    foreach(CurrentPlatformFile IN LISTS PLUGIN_FILES)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CurrentPlatformFile} "${CMAKE_CURRENT_BINARY_DIR}/platforms")
    endforeach()
endif()





