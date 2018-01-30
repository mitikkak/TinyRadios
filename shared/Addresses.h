
#pragma once

static constexpr int maxNumberOfNodes{9};
static constexpr uint8_t led_server_addresses[maxNumberOfNodes][5] = {
    {0xAA, 0xBB, 0xCC, 0xDD, 0x1},
    {0xAA, 0xBB, 0xCC, 0xDD, 0x2},
    {0xAA, 0xBB, 0xCC, 0xDD, 0x3},
    {0xAA, 0xBB, 0xCC, 0xDD, 0x4},
    {0xAA, 0xBB, 0xCC, 0xDD, 0x5},
    {0xAA, 0xBB, 0xCC, 0xDD, 0x6},
    {0xAA, 0xBB, 0xCC, 0xDD, 0x7},
    {0xAA, 0xBB, 0xCC, 0xDD, 0x8},
    {0xAA, 0xBB, 0xCC, 0xDD, 0x9}
};
static constexpr uint8_t led_node_addresses[maxNumberOfNodes][5] = {
    {0xAA, 0xBB, 0xCC, 0xEE, 0x1},
    {0xAA, 0xBB, 0xCC, 0xEE, 0x2},
    {0xAA, 0xBB, 0xCC, 0xEE, 0x3},
    {0xAA, 0xBB, 0xCC, 0xEE, 0x4},
    {0xAA, 0xBB, 0xCC, 0xEE, 0x5},
    {0xAA, 0xBB, 0xCC, 0xEE, 0x6},
    {0xAA, 0xBB, 0xCC, 0xEE, 0x7},
    {0xAA, 0xBB, 0xCC, 0xEE, 0x8},
    {0xAA, 0xBB, 0xCC, 0xEE, 0x9}
};
