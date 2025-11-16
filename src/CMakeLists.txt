cmake_minimum_required(VERSION 3.22.0)

# Automatically find and use the vcpkg submodule
set(VCPKG_TOOLCHAIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../vcpkg/scripts/buildsystems/vcpkg.cmake")

if(EXISTS "${VCPKG_TOOLCHAIN_PATH}")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_TOOLCHAIN_PATH}"
        CACHE STRING "Vcpkg toolchain file")
else()
    message(WARNING "vcpkg submodule not found at '${VCPKG_TOOLCHAIN_PATH}'. 
                     Dependencies will not be built. 
                     Make sure you are in the right directory and ran 'git submodule update --init'.")
endif()

project(SimulationOfEvolution VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Workaround for long paths on Windows (optional, but good to keep)
if(CMAKE_HOST_WIN32)
  set(OBJECT_PATH_MAX 260)
  set(OBJECT_NAME_MAX 255)
endif()

# Find the Qt6 package
# vcpkg will automatically make this available
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Set up standard Qt project settings
qt_standard_project_setup()

# Define your executable
qt_add_executable(${PROJECT_NAME} 
    "Main.cpp" 
    "Neurons.h" "Neurons.cpp" 
    "utilities.h" 
    "Creature.h" "Creature.cpp" 
    "Environment.h" "Environment.cpp" 
    "QtGraphics.cpp" "QtGraphics.h"
)

# Link against the Qt libraries
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)

# Set compiler-specific warning flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wreturn-type)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W2)
endif()

qt_copy_qt_plugins(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
