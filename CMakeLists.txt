cmake_minimum_required(VERSION 3.19)
project(totality VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.h)
file(GLOB_RECURSE UI_FILES CONFIGURE_DEPENDS src/*.ui)
add_executable(totality ${SRC_FILES})
target_link_libraries(totality PRIVATE Qt6::Widgets)

# Additional Options
target_include_directories(totality PRIVATE
    ${Qt6Widgets_INCLUDE_DIRS}
)

# Additional Include Directories
get_target_property(QtWidgetsIncludeDirs Qt6::Widgets INTERFACE_INCLUDE_DIRECTORIES)
foreach(dir IN LISTS QtWidgetsIncludeDirs)
    target_compile_options(totality PRIVATE "/I${dir}")
endforeach()

target_compile_definitions(totality PRIVATE 
    QT_DEBUG
    QT_QML_DEBUG
)

get_filename_component(Qt6_BIN_DIR "${Qt6_DIR}/../../../bin" ABSOLUTE)
# here copying of qt in build dir
#if(WIN32)
#    add_custom_command(TARGET totality POST_BUILD
#        COMMENT "Running windeployqt to deploy Qt6 dependencies"
#        COMMAND "${Qt6_BIN_DIR}/windeployqt.exe"  --debug  "$<TARGET_FILE:totality>"
#        VERBATIM
#    )
#endif()

# --- install: собираем exe + Qt DLL в папку dist ---
install(TARGETS totality
    RUNTIME DESTINATION .
)

if(WIN32)
    install(CODE "
        set(CMAKE_INSTALL_PREFIX dist)
        message(STATUS \"Install prefix: ${CMAKE_INSTALL_PREFIX}\")
        message(STATUS \"Running windeployqt for install...\")
        execute_process(
            COMMAND \"${Qt6_BIN_DIR}/windeployqt.exe\" --no-compiler-runtime \"${CMAKE_INSTALL_PREFIX}/totality.exe\"
            RESULT_VARIABLE _err
            OUTPUT_VARIABLE _out
            ERROR_VARIABLE _errout
        )
        message(STATUS \"windeployqt output:\\n${_out}\")
        message(STATUS \"windeployqt errors:\\n${_errout}\")
        if(NOT _err EQUAL 0)
            message(FATAL_ERROR \"windeployqt failed with exit code \${_err}\")
        endif()
    ")
endif()
