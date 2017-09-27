#include <iostream>
#include <memory>
#include <unistd.h>
#include "streamer.hpp"

int main(int argc, char* argv[]) {

    //don't care
    (void)argc;
    (void)argv;

    //get device idx
    uint32_t device_idx;
    std::cout << "Device idx: ";
    std::cin >> device_idx;

    //open streamer
    auto streamer = std::make_shared<Streamer>(device_idx);

    //test out the threaded display
    uint32_t display_seconds;
    std::cout << "Time to display: ";
    std::cin >> display_seconds;

    streamer->startDisplay("Timed display");
    sleep(display_seconds);
    streamer->stopDisplay();
}
