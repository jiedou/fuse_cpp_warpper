add_executable(hello hello.cpp)
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
#target_link_libraries(hello)