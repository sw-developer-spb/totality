cmake_minimum_required(VERSION 3.19)
project(totality VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.h)
add_executable(totality ${SRC_FILES})
target_link_libraries(totality PRIVATE Qt6::Widgets)

if(WIN32)
    get_filename_component(Qt6_BIN_DIR "${Qt6_DIR}/../../../bin" ABSOLUTE)
    add_custom_command(TARGET totality POST_BUILD
        COMMENT "Running windeployqt to deploy Qt6 dependencies"
        COMMAND "${Qt6_BIN_DIR}/windeployqt.exe" "$<TARGET_FILE:totality>"
        VERBATIM
    )
endif()