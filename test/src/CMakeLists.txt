cmake_minimum_required(VERSION 3.10)

project(hiacejs_test)

# hiacejs_test
list(APPEND hiacejs_test_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/src/foundation/ace/frameworks/lite/targets/hybridos
)

list(APPEND hiacejs_test_SOURCES
    main.c
)

include_directories(${hiacejs_test_INCLUDE_DIRECTORIES})
add_executable(hiacejs_test ${hiacejs_test_SOURCES})
target_link_libraries(hiacejs_test ace ${JERRYSCRIPT_LIBRARIES})
install(TARGETS hiacejs_test DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
