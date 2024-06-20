## We are using vcpkg as a fetchContent package `https://github.com/microsoft/vcpkg/issues/30572`

include(FetchContent)

set(FC_PACKAGE_NAME vcpkg)

FetchContent_Declare(
    ${FC_PACKAGE_NAME}
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG        master
    ## The SOURCE_DIR would fix the problem mentioned here https://github.com/microsoft/vcpkg/pull/27311, but we dont mind a bit slower configure step.
    # SOURCE_DIR     "${PROJECT_SOURCE_DIR}/vcpkg"
    # QUIET
)

FetchContent_MakeAvailable(${FC_PACKAGE_NAME})

## probably doesnt work, but still...
set(ENV{VCPKG_DISABLE_METRICS} ON)

## This unfortunally does not work - it needs to be set in the triplet - but maybe later this will be usefull `https://github.com/microsoft/vcpkg/issues/1626`
# set(VCPKG_BUILD_TYPE release CACHE BOOL "Build only release")

set(CMAKE_TOOLCHAIN_FILE "${${FC_PACKAGE_NAME}_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "Vcpkg toolchain file")

## Later when CMAKE_PROJECT_TOP_LEVEL_INCLUDES gains popularity this could be used `https://github.com/microsoft/vcpkg/discussions/26681`
#list(APPEND CMAKE_PROJECT_TOP_LEVEL_INCLUDES "${${FC_PACKAGE_NAME}_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake")
#list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES CMAKE_PROJECT_TOP_LEVEL_INCLUDES)
