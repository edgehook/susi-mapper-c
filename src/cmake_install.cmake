# Install script for directory: /home/james/susi-mapper/susi-mapper-c/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/james/susi-mapper/susi-mapper-c/out")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/james/susi-mapper/susi-mapper-c/out/lib" TYPE SHARED_LIBRARY FILES "/home/james/susi-mapper/susi-mapper-c/src/libmapper-core.so.1.0.0")
  if(EXISTS "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0"
         OLD_RPATH "/home/james/susi-mapper/susi-mapper-c/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/james/susi-mapper/susi-mapper-c/out/lib" TYPE SHARED_LIBRARY FILES "/home/james/susi-mapper/susi-mapper-c/src/libmapper-core.so")
  if(EXISTS "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so"
         OLD_RPATH "/home/james/susi-mapper/susi-mapper-c/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c/mapper-core-cConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c/mapper-core-cConfig.cmake"
         "/home/james/susi-mapper/susi-mapper-c/src/CMakeFiles/Export/_home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c/mapper-core-cConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c/mapper-core-cConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}/home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c/mapper-core-cConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c/mapper-core-cConfig.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c" TYPE FILE FILES "/home/james/susi-mapper/susi-mapper-c/src/CMakeFiles/Export/_home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c/mapper-core-cConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c/mapper-core-cConfig-noconfig.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c" TYPE FILE FILES "/home/james/susi-mapper/susi-mapper-c/src/CMakeFiles/Export/_home/james/susi-mapper/susi-mapper-c/out/lib/cmake/mapper-core-c/mapper-core-cConfig-noconfig.cmake")
  endif()
endif()

