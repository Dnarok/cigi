#include "cigi/host/ig_control.hpp"
#include "cigi/host/entity_control.hpp"
#include "cigi/host/conformal_clamped_entity_control.hpp"
#include "cigi/host/component_control.hpp"
#include "cigi/host/short_component_control.hpp"
#include "cigi/host/articulated_part_control.hpp"
#include "cigi/host/short_articulated_part_control.hpp"
#include "cigi/host/rate_control.hpp"
#include "cigi/host/celestial_sphere_control.hpp"
#include "cigi/host/atmosphere_control.hpp"
#include "cigi/host/environmental_region_control.hpp"
#include "cigi/host/weather_control.hpp"
#include "cigi/host/maritime_surface_conditions_control.hpp"
#include "cigi/host/wave_control.hpp"
#include "cigi/host/terrestrial_surface_conditions_control.hpp"
#include "cigi/host/view_control.hpp"
#include "cigi/host/sensor_control.hpp"
#include "cigi/host/motion_tracker_control.hpp"
#include "cigi/host/earth_reference_model_definition.hpp"
#include "cigi/host/trajectory_definition.hpp"
#include "cigi/host/view_definition.hpp"
#include "cigi/host/collision_detection_segment_definition.hpp"
#include "cigi/host/collision_detection_volume_definition.hpp"
#include "cigi/host/hat_hot_request.hpp"
#include "cigi/host/line_of_sight_segment_request.hpp"
#include "cigi/host/line_of_sight_vector_request.hpp"
#include "cigi/host/position_request.hpp"
#include "cigi/host/environmental_conditions_request.hpp"
#include "cigi/host/symbol_surface_definition.hpp"
#include "cigi/host/symbol_text_definition.hpp"
#include "cigi/host/symbol_circle_definition.hpp"
#include "cigi/host/symbol_line_definition.hpp"
#include "cigi/host/symbol_clone.hpp"
#include "cigi/host/symbol_control.hpp"
#include "cigi/host/short_symbol_control.hpp"

#include <iostream>

#include <gtest/gtest.h>

TEST(host_packets, print_host_packets)
{
    cigi::ig_control igc;
    std::cout << igc << "\n\n";

    cigi::entity_control ec;
    std::cout << ec << "\n\n";

    cigi::conformal_clamped_entity_control ccec;
    std::cout << ccec << "\n\n";

    cigi::component_control cc;
    cc.set_bit(true, 191);
    std::cout << cc << "\n\n";

    cigi::short_component_control scc;
    scc.set_bit(true, 63);
    std::cout << scc << "\n\n";

    cigi::articulated_part_control apc;
    std::cout << apc << "\n\n";

    cigi::short_articulated_part_control sapc;
    std::cout << sapc << "\n\n";

    cigi::rate_control rc;
    std::cout << rc << "\n\n";

    cigi::celestial_sphere_control csc;
    std::cout << csc << "\n\n";

    cigi::atmosphere_control ac;
    std::cout << ac << "\n\n";

    cigi::environmental_region_control erc;
    std::cout << erc << "\n\n";

    cigi::weather_control wc;
    std::cout << wc << "\n\n";

    cigi::maritime_surface_conditions_control mscc;
    std::cout << mscc << "\n\n";

    cigi::wave_control wac;
    std::cout << wac << "\n\n";

    cigi::terrestrial_surface_conditions_control tscc;
    std::cout << tscc << "\n\n";

    cigi::view_control vc;
    std::cout << vc << "\n\n";

    cigi::sensor_control sc;
    std::cout << sc << "\n\n";

    cigi::motion_tracker_control mtc;
    std::cout << mtc << "\n\n";

    cigi::earth_reference_model_definition ermd;
    std::cout << ermd << "\n\n";

    cigi::trajectory_definition td;
    std::cout << td << "\n\n";

    cigi::view_definition vd;
    std::cout << vd << "\n\n";

    cigi::collision_detection_segment_definition cdsd;
    std::cout << cdsd << "\n\n";

    cigi::collision_detection_volume_definition cdvd;
    std::cout << cdvd << "\n\n";

    cigi::hat_hot_request hhr;
    std::cout << hhr << "\n\n";

    cigi::line_of_sight_segment_request lossr;
    std::cout << lossr << "\n\n";

    cigi::line_of_sight_vector_request losvr;
    std::cout << losvr << "\n\n";

    cigi::position_request pr;
    std::cout << pr << "\n\n";

    cigi::environmental_conditions_request ecr;
    ecr.request_type = cigi::environmental_conditions_request::request_type_t::maritime_surface_conditions | cigi::environmental_conditions_request::request_type_t::aerosol_concentrations;
    std::cout << ecr << "\n\n";

    cigi::symbol_surface_definition ssd;
    std::cout << ssd << "\n\n";

    cigi::symbol_text_definition std;
    std.set_text("Hello World!");
    std::cout << std << "\n\n";

    cigi::symbol_circle_definition scd;
    scd.add_arc({});
    scd.add_arc({});
    scd.add_arc({});
    scd.add_arc({});
    std::cout << scd << "\n\n";

    cigi::symbol_line_definition sld;
    sld.add_vertex({});
    sld.add_vertex({});
    sld.add_vertex({});
    sld.add_vertex({});
    sld.add_vertex({});
    sld.add_vertex({});
    std::cout << sld << "\n\n";

    cigi::symbol_clone sc1;
    std::cout << sc1 << "\n\n";

    cigi::symbol_control sc2;
    std::cout << sc2 << "\n\n";

    cigi::short_symbol_control ssc;
    ssc.set_color(0, 255, 127, 63, 31);
    ssc.set_position_u(1, 1.2e34f);
    std::cout << ssc << "\n\n";
};