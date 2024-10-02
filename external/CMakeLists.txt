if (BUILD_TESTS AND NOT TARGET googletest)
	add_subdirectory(googletest)
endif()