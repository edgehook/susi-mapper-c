#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mapper-core-c::mapper-core" for configuration ""
set_property(TARGET mapper-core-c::mapper-core APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(mapper-core-c::mapper-core PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0"
  IMPORTED_SONAME_NOCONFIG "libmapper-core.so.1.0.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS mapper-core-c::mapper-core )
list(APPEND _IMPORT_CHECK_FILES_FOR_mapper-core-c::mapper-core "/home/james/susi-mapper/susi-mapper-c/out/lib/libmapper-core.so.1.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
