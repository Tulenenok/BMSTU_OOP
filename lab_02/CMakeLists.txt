cmake_minimum_required(VERSION 3.20)
project(my_lab_02)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_lab_02 main.cpp inc/BaseContainer.h inc/BaseIter.h src/BaseContainter.cpp src/BaseIter.cpp tests/vectorTests.cpp inc/Vector.h imp/Vector.hpp inc/Iterator.h tests/vectorTests.h tests/tools.h tests/tools.cpp inc/BaseException.h src/BaseException.cpp inc/Exceptions.h inc/ConstIterator.h)
