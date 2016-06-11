cmake_minimum_required (VERSION 2.8.12)

project(slight_lisp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
option(SLIGHTLISP_BUILD_TEST "build unit tests" ON)


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
  message(FATAL_ERROR
    "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

include(ExternalProject)
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)
include(External_editline)

include_directories(
  include
  ${EDITLINE_INCLUDE_DIRS}
)

add_library(slightlisp
  "src/env.cpp"
  "src/eval.cpp"
  "src/special_forms.cpp"
  "src/value.cpp"
)

add_executable(slightlisp-repl
  "src/repl.cpp")

target_link_libraries(slightlisp-repl
  slightlisp
  ${EDITLINE_LIBRARY})

if(SLIGHTLISP_BUILD_TESTS)
  include(External_GMock)
  enable_testing()
  include_directories(${GTEST_INCLUDE_DIRS})
  include_directories(${GMOCK_INCLUDE_DIRS})

  add_executable(test_parser "tests/test_parser.cpp")
  target_link_libraries(test_parser
    slightlisp
    ${GMOCK_MAIN_LIBRARY})
  add_test(ParserTests test_parser)

  add_executable(test_value "tests/test_value.cpp")
  target_link_libraries(test_value
    slightlisp
    ${GMOCK_MAIN_LIBRARY}
    )
  add_test(TypeValue test_value)

  add_executable(test_env "tests/test_env.cpp")
  target_link_libraries(test_env
    slightlisp
    ${GMOCK_MAIN_LIBRARY}
    )
  add_test(TypeTests test_env)
  
  add_executable(test_special_forms "tests/test_special_forms.cpp")
  target_link_libraries(test_special_forms
    slightlisp
    ${GMOCK_MAIN_LIBRARY}
    )
  add_test(SpecialFormTests test_special_forms)

  add_executable(test_eval "tests/test_eval.cpp")
  target_link_libraries(test_eval
    slightlisp
    ${GMOCK_MAIN_LIBRARY}
    )
  add_test(TypeTests test_eval)
endif()
