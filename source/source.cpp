#include "header.hpp"

auto test(int value) -> int
{
    contract;
        pre(value == 1);
        post(value == 3);
    spdlog::info("Hello, {}!", fmt::format("{}", value));

    cond(value == 2);

    return value * 2;
};