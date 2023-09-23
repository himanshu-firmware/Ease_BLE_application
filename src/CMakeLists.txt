cmake_minimum_required(VERSION 3.21)

set (CMAKE_FILES_PATH D:/stimveda_codebase/ble_windows/SimpleBLE/cmake)

include(${CMAKE_FILES_PATH}/prelude.cmake)

project(Ease_app 
    VERSION 0.1.0)

include(${CMAKE_FILES_PATH}/epilogue.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SIMPLEBLE_LOCAL "Use local SimpleBLE Files" ON)

if (SIMPLEBLE_LOCAL)
    add_subdirectory(D:/stimveda_codebase/ble_windows/SimpleBLE/simpleble  ${CMAKE_BINARY_DIR}/simpleble)
else()
    find_package(simpleble CONFIG REQUIRED)
endif()


set(EASE_APP_SOURCE_FILES 
    Ease_ble_app/Ease_app.cpp
    Ease_ble_app/Ease_app_connect.cpp
    Ease_ble_app/utils.cpp )

set(EASE_APP_INCLUDES_DIR
    Ease_ble_app )

# CPP
add_executable(EASE_APP ${EASE_APP_SOURCE_FILES})
target_include_directories(EASE_APP PUBLIC ${EASE_APP_INCLUDES_DIR})
target_link_libraries(EASE_APP simpleble::simpleble)

