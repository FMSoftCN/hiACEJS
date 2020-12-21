cmake_minimum_required(VERSION 3.10)

project(hiacejs_run)

# hiacejs_run
list(APPEND hiacejs_run_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/src/foundation/ace/frameworks/lite/targets/hybridos
)

list(APPEND hiacejs_run_SOURCES
    main.c
)

include_directories(${hiacejs_run_INCLUDE_DIRECTORIES})
add_executable(hiacejs_run ${hiacejs_run_SOURCES})
target_link_libraries(hiacejs_run hiacejs ${JERRYSCRIPT_LIBRARIES} ${MINIGUI_LIBRARIES})
install(TARGETS hiacejs_run DESTINATION bin)
