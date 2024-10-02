cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)

set(MY_PROJECT_NAME cigi)
project(
    ${MY_PROJECT_NAME}
    LANGUAGES CXX
    VERSION   1.0
)

option(BUILD_TESTS "Build the tests" ON)
add_subdirectory(external)

add_library(${MY_PROJECT_NAME}
    include/cigi/general.hpp
    include/cigi/session.hpp
    include/cigi/socket.hpp

    include/cigi/host/articulated_part_control.hpp
    include/cigi/host/atmosphere_control.hpp
    include/cigi/host/celestial_sphere_control.hpp
    include/cigi/host/collision_detection_segment_definition.hpp
    include/cigi/host/collision_detection_volume_definition.hpp
    include/cigi/host/component_control.hpp
    include/cigi/host/conformal_clamped_entity_control.hpp
    include/cigi/host/earth_reference_model_definition.hpp
    include/cigi/host/entity_control.hpp
    include/cigi/host/environmental_conditions_request.hpp
    include/cigi/host/environmental_region_control.hpp
    include/cigi/host/hat_hot_request.hpp
    include/cigi/host/ig_control.hpp
    include/cigi/host/line_of_sight_segment_request.hpp
    include/cigi/host/line_of_sight_vector_request.hpp
    include/cigi/host/maritime_surface_conditions_control.hpp
    include/cigi/host/motion_tracker_control.hpp
    include/cigi/host/position_request.hpp
    include/cigi/host/rate_control.hpp
    include/cigi/host/sensor_control.hpp
    include/cigi/host/short_articulated_part_control.hpp
    include/cigi/host/short_component_control.hpp
    include/cigi/host/short_symbol_control.hpp
    include/cigi/host/symbol_circle_definition.hpp
    include/cigi/host/symbol_clone.hpp
    include/cigi/host/symbol_control.hpp
    include/cigi/host/symbol_line_definition.hpp
    include/cigi/host/symbol_surface_definition.hpp
    include/cigi/host/symbol_text_definition.hpp
    include/cigi/host/terrestrial_surface_conditions_control.hpp
    include/cigi/host/trajectory_definition.hpp
    include/cigi/host/view_control.hpp
    include/cigi/host/view_definition.hpp
    include/cigi/host/wave_control.hpp
    include/cigi/host/weather_control.hpp

    include/cigi/ig/aerosol_concentration_response.hpp
    include/cigi/ig/animation_stop_notification.hpp
    include/cigi/ig/collision_detection_segment_notification.hpp
    include/cigi/ig/collision_detection_volume_notification.hpp
    include/cigi/ig/event_notification.hpp
    include/cigi/ig/hat_hot_extended_response.hpp
    include/cigi/ig/hat_hot_response.hpp
    include/cigi/ig/image_generator_message.hpp
    include/cigi/ig/line_of_sight_extended_response.hpp
    include/cigi/ig/line_of_sight_response.hpp
    include/cigi/ig/maritime_surface_conditions_response.hpp
    include/cigi/ig/position_response.hpp
    include/cigi/ig/sensor_extended_response.hpp
    include/cigi/ig/sensor_response.hpp
    include/cigi/ig/start_of_frame.hpp
    include/cigi/ig/terrestrial_surface_conditions_response.hpp
    include/cigi/ig/weather_conditions_response.hpp

    source/socket.cpp
)

target_include_directories(${MY_PROJECT_NAME} 
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cigi>
           $<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()