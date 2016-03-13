include_directories("../src")

add_executable(test-main test-main.c)
add_executable(test-cxx test-cxx.cc)

target_link_libraries(test-main c-util)
target_link_libraries(test-cxx c-util)
