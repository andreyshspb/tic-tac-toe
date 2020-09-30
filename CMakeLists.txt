cmake_minimum_required(VERSION 3.10)
project(hw_02)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(hw_02 src/main.cpp include/Board.hpp src/Board.cpp include/StdioBoardView.hpp
               src/StdioBoardView.cpp include/NcursesBoardView.hpp src/NcursesBoardView.cpp src/GameController.cpp include/GameController.hpp include/BoardView.hpp)
add_executable(test_hw_02 test/test.cpp test/BoardTest.cpp include/BoardTest.hpp
               test/Test.cpp include/Test.hpp include/Board.hpp src/Board.cpp)

target_link_libraries(hw_02 ncurses)
