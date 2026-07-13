cmake_minimum_required(VERSION 3.22.0)

# --- Locate vcpkg toolchain (must be set before project()) -------------------
# Priority: an explicitly-passed toolchain > $VCPKG_ROOT > a ./vcpkg submodule
# at the repository root. This keeps the build working whether the person uses
# a system vcpkg or vendors it as a submodule.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VCPKG_ROOT} AND EXISTS "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
    else()
        message(WARNING
            "vcpkg not found. Set the VCPKG_ROOT environment variable, or add vcpkg as a "
            "submodule at the repository root (git submodule add https://github.com/microsoft/vcpkg). "
            "Dependencies (Qt6) will not be resolved without it.")
    endif()
endif()

project(SimulationOfEvolution VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Workaround for long paths on Windows
if(CMAKE_HOST_WIN32)
    set(OBJECT_PATH_MAX 260)
    set(OBJECT_NAME_MAX 255)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    "Main.cpp"
    "Neurons.h" "Neurons.cpp"
    "utilities.h"
    "Creature.h" "Creature.cpp"
    "Environment.h" "Environment.cpp"
    "QtGraphics.cpp" "QtGraphics.h"
)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)

# Treat return-type mistakes as errors; keep warnings visible.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror=return-type)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
endif()

qt_copy_qt_plugins(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
