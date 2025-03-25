# source files = $SRC_FILES
add_subdirectory(./wiiuse_src)
# headers
include_directories(./wiiuse_src)

# source files
set(
    SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ble_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/wiimote_handler.c
    ${CMAKE_CURRENT_LIST_DIR}/connection_listener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client.cpp
    ${SOURCES}
    PARENT_SCOPE
)
