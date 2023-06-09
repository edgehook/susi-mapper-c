SET(susi_src
	susi-mapper.c
    	dev.c
	)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

MESSAGE(STATUS "paho library: ${PAHO_MQTT3a_LIB}")
MESSAGE(STATUS "susi paho mqtt hints: ${PAHO_MQTT3c_LIB}")

ADD_EXECUTABLE(susi-mapper ${susi_src})
TARGET_LINK_LIBRARIES(susi-mapper
	mapper-core
	${PAHO_MQTT3a_LIB} 
	${PAHO_MQTT3c_LIB}
	${SUSI_LIB}
	${LIBS_SYSTEM})

INSTALL(TARGETS susi-mapper
        LIBRARY DESTINATION  ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION  ${CMAKE_INSTALL_BINDIR}
	ARCHIVE DESTINATION  ${CMAKE_INSTALL_LIBDIR})

GET_FILENAME_COMPONENT(LIB_BASE_PATH ${PAHO_MQTT3a_LIB} PATH)
IF (WIN32)
	FILE(GLOB allCopyFiles  "${LIB_BASE_PATH}/paho-mqtt3*.dll")
	INSTALL(FILES
		${allCopyFiles} 
		DESTINATION ${CMAKE_INSTALL_BINDIR})
ELSE()
	FILE(GLOB allCopyFiles  "${LIB_BASE_PATH}/libpaho-mqtt3*.so.*")
	INSTALL(FILES
		${allCopyFiles} 
		DESTINATION ${CMAKE_INSTALL_LIBDIR})
ENDIF()
