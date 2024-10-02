#include "cigi/session.hpp"
#include "cigi/host/symbol_text_definition.hpp"

#include <iostream>
#include <thread>

#include <gtest/gtest.h>

#pragma comment(lib, "Ws2_32.lib")

TEST(other, test_network)
{
    cigi::symbol_text_definition std1;
    std1.symbol_id = 0xDEAD;
    std1.alignment = cigi::symbol_text_definition::alignment_t::bottom_center;
    std1.orientation = cigi::symbol_text_definition::orientation_t::right_to_left;
    std1.font_id = cigi::symbol_text_definition::font_t::monospace_serif;
    std1.font_size = 1.2e34f;
    std1.set_text("Hello World!");

    std::cout << std1 << "\n\n";

    cigi::session_network session;
    session.connect("127.255.255.255", 34567, 34567);
    session.write(std1);

    std::jthread write_thread
    {
        [&session, &std1]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
            session.flush();
        }
    };

    auto future = session.read_async<cigi::symbol_text_definition>(std::launch::async);
    std::this_thread::sleep_for(std::chrono::seconds{ 1 });
    std::cout << future.get() << "\n\n";
};