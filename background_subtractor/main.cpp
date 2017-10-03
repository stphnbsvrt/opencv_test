#include <iostream>
#include <memory>
#include <unistd.h>
#include "fgStreamer.hpp"

int main(int argc, char* argv[]) {

    //don't care
    (void)argc;
    (void)argv;

    //get device idx
    uint32_t device_idx;
    std::cout << "Device idx: ";
    std::cin >> device_idx;

    //get subtractor type
    uint32_t subtractor_type;
    std::cout << "Subtractor type: ";
    std::cin >> subtractor_type;

    //get blurring square size
    uint32_t blur_kernel_width;
    std::cout << "Blur kernel size: ";
    std::cin >> blur_kernel_width;

    //open streamer
    auto streamer = std::make_shared<FGStreamer>(device_idx, subtractor_type);
    streamer->addFilter(Filter::Type::BLUR, {blur_kernel_width, blur_kernel_width});

    //test out the threaded display
    uint32_t display_seconds;
    std::cout << "Time to display: ";
    std::cin >> display_seconds;

    streamer->startDisplay("Timed display");
    sleep(display_seconds);
    streamer->stopDisplay();
}
