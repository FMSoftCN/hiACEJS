cmake_minimum_required(VERSION 3.10)

project(appagent)

# appagent
list(APPEND appagent_INCLUDE_DIRECTORIES
)

list(APPEND appagent_SOURCES
    src/main.cpp
)

include_directories(${appagent_INCLUDE_DIRECTORIES})
add_executable(appagent ${appagent_SOURCES})
target_link_libraries(appagent ${MINIGUI_LIBRARIES})
install(TARGETS appagent DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
