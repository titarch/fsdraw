add_subdirectory(utils)
add_subdirectory(shapes)
add_subdirectory(engine)

add_executable(${EXECUTABLE_NAME} main.cc)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(shapes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

target_link_libraries(${EXECUTABLE_NAME} engine shapes utils)
target_link_libraries(${EXECUTABLE_NAME} sfml-window sfml-graphics)
