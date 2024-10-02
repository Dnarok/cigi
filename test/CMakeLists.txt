project(tests
	LANGUAGES CXX
	VERSION   1.0
)

add_executable(default_test
	default_test.cpp
)
target_link_libraries(default_test
	PRIVATE ${MY_PROJECT_NAME}
	PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(default_test)