cmake_minimum_required(VERSION 3.24)
include(CMakePrintHelpers)

set(CMAKE_CXX_STANDARD 17)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(Task_1 VERSION  ${PROJECT_VERSION})
configure_file(version.h.in version.h)

set(Boost_DBUG ON)
set(Boost_ROOT "C:/Program Files/boost_1_81_0")
find_package(Boost COMPONENTS)

add_executable(Task_1 main.cpp)
set_target_properties(Task_1 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(Task_1 PRIVATE "${CMAKE_BINARY_DIR}")

cmake_print_variables(Boost_INCLUDE_DIR)

install(TARGETS Task_1 RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)
