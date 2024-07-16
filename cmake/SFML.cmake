# Copy SFML-related DLLs to the target folder
if(WIN32)
	if(NOT SFML_FOUND)
		configure_file ("${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll" ${CMAKE_BINARY_DIR} COPYONLY)
	else()
		configure_file ("${SFML_LOCATION}/bin/openal32.dll" ${CMAKE_BINARY_DIR} COPYONLY)
	endif()

endif()

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)
