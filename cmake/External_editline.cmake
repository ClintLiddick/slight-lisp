ExternalProject_Add(
  editline_ext
  GIT_REPOSITORY https://github.com/troglobit/editline.git
  UPDATE_COMMAND ""
  GIT_TAG "1.15.2"
  CONFIGURE_COMMAND   <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/src/.libs
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON)

ExternalProject_Add_Step(editline_ext autogen
  COMMAND <SOURCE_DIR>/autogen.sh
  WORKING_DIRECTORY <SOURCE_DIR>
  DEPENDEES patch
  DEPENDERS configure)


ExternalProject_Get_Property(editline_ext install_dir)
set(EDITLINE_INCLUDE_DIRS ${install_dir}/include)
set(EDITLINE_LIBRARY_PATH "${install_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}editline.so")
set(EDITLINE_LIBRARY editline)
add_library(${EDITLINE_LIBRARY} UNKNOWN IMPORTED)
set_target_properties(${EDITLINE_LIBRARY} PROPERTIES
  IMPORTED_LOCATION ${EDITLINE_LIBRARY_PATH})
add_dependencies(${EDITLINE_LIBRARY} editline_ext)
