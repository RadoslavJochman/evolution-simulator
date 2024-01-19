cmake_minimum_required(VERSION 3.16...3.22)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
include(AutoVcpkg)

vcpkg_install(qtbase)
vcpkg_install(matplotplusplus)



project(SimulationOfEvolution CXX)
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
endif (MSVC)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Matplot++ REQUIRED)




qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    "Main.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Widgets Matplot++::matplot)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}\\out\\build\\x64-debug\\vcpkg\\installed\\x64-windows\\debug\\Qt6\\plugins\\platforms"
            "${PROJECT_SOURCE_DIR}\\out\\build\\x64-debug\\platforms")
else()
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}\\out\\build\\x64-release\\vcpkg\\installed\\x64-windows\\Qt6\\plugins\\platforms"
            "${PROJECT_SOURCE_DIR}\\out\\build\\x64-release\\platforms")
endif()