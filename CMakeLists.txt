cmake_minimum_required (VERSION 2.8.12)

project(slight_lisp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
option(SLIGHTLISP_BUILD_TEST "build unit tests" ON)


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
  message(FATAL_ERROR
    "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

include_directories(include)

if(SLIGHTLISP_BUILD_TESTS)
  include(ExternalProject)
  set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)

  include(External_GMock)
  enable_testing()
  # find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})
  include_directories(${GMOCK_INCLUDE_DIRS})
  # message(WARNING "CLINT: ${GTEST_INCLUDE_DIRS}")
  # message(WARNING "CLINT: ${GTEST_LIBRARY_PATH}")
  # message(WARNING "CLINT: ${GTEST_MAIN_LIBRARY_PATH}")
  # message(WARNING "CLINT: ${GMOCK_INCLUDE_DIRS}")
  # message(WARNING "CLINT: ${GMOCK_LIBRARY_PATH}")
  # message(WARNING "CLINT: ${GMOCK_MAIN_LIBRARY_PATH}")

  add_executable(test_parser "tests/test_parser.cpp")
  target_link_libraries(test_parser
    ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY}
    ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY})
  add_test(ParserTests test_parser)
endif()
