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


# cmake_minimum_required(VERSION 3.21)

# set(CMAKE_SIMPLE_BLE_DIR D:/stimveda_codebase/ble_windows/SimpleBLE)

# include(${CMAKE_SIMPLE_BLE_DIR}/cmake/prelude.cmake)
# project(simpleble_examples)
# include(${CMAKE_SIMPLE_BLE_DIR}/cmake/epilogue.cmake)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_EXTENSIONS OFF)

# option(SIMPLEBLE_LOCAL "Use local SimpleBLE" ON)

# if (SIMPLEBLE_LOCAL)
#     add_subdirectory(${CMAKE_SIMPLE_BLE_DIR}/simpleble ${CMAKE_BINARY_DIR}/simpleble)
# else()
#     find_package(simpleble CONFIG REQUIRED)
# endif()

# # C++
# add_subdirectory(cpp/list_adapters)
# add_subdirectory(cpp/list_adapters_safe)
# add_subdirectory(cpp/scan)
# add_subdirectory(cpp/connect)
# add_subdirectory(cpp/connect_safe)
# add_subdirectory(cpp/multiconnect)
# add_subdirectory(cpp/read)
# add_subdirectory(cpp/write)
# add_subdirectory(cpp/notify)
# add_subdirectory(cpp/notify_multi)

# # C
# add_executable(example_connect_c c/connect.c)
# target_link_libraries(example_connect_c simpleble::simpleble-c)

# add_executable(example_notify_c c/notify.c)
# target_link_libraries(example_notify_c simpleble::simpleble-c)

# add_executable(example_scan_c c/scan.c)
# target_link_libraries(example_scan_c simpleble::simpleble-c)

