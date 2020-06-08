add_executable(bst_tests_run bstTest.cpp catch_main.cpp ../util.h ../util.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -pedantic --coverage")