#include "cigi/ig/start_of_frame.hpp"
#include "cigi/ig/hat_hot_response.hpp"
#include "cigi/ig/hat_hot_extended_response.hpp"
#include "cigi/ig/line_of_sight_response.hpp"
#include "cigi/ig/line_of_sight_extended_response.hpp"
#include "cigi/ig/sensor_response.hpp"
#include "cigi/ig/sensor_extended_response.hpp"
#include "cigi/ig/position_response.hpp"
#include "cigi/ig/weather_conditions_response.hpp"
#include "cigi/ig/aerosol_concentration_response.hpp"
#include "cigi/ig/maritime_surface_conditions_response.hpp"
#include "cigi/ig/terrestrial_surface_conditions_response.hpp"
#include "cigi/ig/collision_detection_segment_notification.hpp"
#include "cigi/ig/collision_detection_volume_notification.hpp"
#include "cigi/ig/animation_stop_notification.hpp"
#include "cigi/ig/event_notification.hpp"
#include "cigi/ig/image_generator_message.hpp"

#include <iostream>

#include <gtest/gtest.h>

TEST(ig_packets, print_ig_packets)
{
    cigi::start_of_frame sof;
    std::cout << sof << "\n\n";

    cigi::hat_hot_response hhr;
    std::cout << hhr << "\n\n";

    cigi::hat_hot_extended_response hher;
    std::cout << hher << "\n\n";

    cigi::line_of_sight_response losr;
    std::cout << losr << "\n\n";

    cigi::line_of_sight_extended_response loser;
    std::cout << loser << "\n\n";

    cigi::sensor_response sr;
    std::cout << sr << "\n\n";

    cigi::sensor_extended_response ser;
    std::cout << ser << "\n\n";

    cigi::position_response pr;
    std::cout << pr << "\n\n";

    cigi::weather_conditions_response wcr;
    std::cout << wcr << "\n\n";

    cigi::aerosol_concentration_response acr;
    std::cout << acr << "\n\n";

    cigi::maritime_surface_conditions_response mscr;
    std::cout << mscr << "\n\n";

    cigi::terrestrial_surface_conditions_response tscr;
    std::cout << tscr << "\n\n";

    cigi::collision_detection_segment_notification cdsn;
    std::cout << cdsn << "\n\n";

    cigi::collision_detection_volume_notification cdvn;
    std::cout << cdvn << "\n\n";

    cigi::animation_stop_notification asn;
    std::cout << asn << "\n\n";

    cigi::event_notification en;
    en.set_f64(1.23e45, 1);
    std::cout << en << "\n\n";

    cigi::image_generator_message igm;
    igm.set_message("Hello World!");
    std::cout << igm << "\n\n";
};