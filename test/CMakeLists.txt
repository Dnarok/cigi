project(tests
	LANGUAGES CXX
	VERSION   1.0
)

add_executable(default_test
	default_test.cpp
	host_packets.cpp
	ig_packets.cpp
	other.cpp
)
target_link_libraries(default_test
	PRIVATE ${MY_PROJECT_NAME}
	PRIVATE GTest::gtest_main
)
target_compile_features(default_test
    PUBLIC cxx_std_23
)

include(GoogleTest)
gtest_discover_tests(default_test)