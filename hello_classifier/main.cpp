#include <iostream>
#include <memory>
#include <unistd.h>
#include "classifier.hpp"

int main(int argc, char* argv[]) {

    //don't care
    (void)argc;
    (void)argv;
    std::string prototxt = _SOURCE_DIR_"/hello_classifier/bvlc_googlenet.prototxt";
    std::string caffe_model = _SOURCE_DIR_"/hello_classifier/bvlc_googlenet.caffemodel";
    std::string classes = _SOURCE_DIR_"/hello_classifier/synset_words.txt";

    //get device idx
    uint32_t device_idx;
    std::cout << "Device idx: ";
    std::cin >> device_idx;

    //open streamer
    std::shared_ptr<Streamer> streamer = std::make_shared<Classifier>(device_idx, prototxt, caffe_model, classes);

    //test out the threaded display
    uint32_t display_seconds;
    std::cout << "Time to display: ";
    std::cin >> display_seconds;

    streamer->startDisplay("Timed display");
    sleep(display_seconds);
    streamer->stopDisplay();
}
