#include "main.hpp"
#include "streamer.hpp"

//
// tests assume camera device idx is valid
//

TEST(StreamerTest, noStopDisplay) {

    Streamer my_streamer(0);
    my_streamer.startDisplay("no stop");
    sleep(1);

    //don't die here
}

TEST(StreamerTest, restartDisplay) {
    
    Streamer my_streamer(0);
    my_streamer.startDisplay("first");
    sleep(1);
    my_streamer.stopDisplay();
    sleep(1);
    my_streamer.startDisplay("second");
    sleep(1);
    my_streamer.stopDisplay();
}

TEST(StreamerTest, smoothDisplay) {

    Streamer my_streamer(0);
    my_streamer.startDisplay("Smoothing");
    sleep(1);
    my_streamer.addFilter(Filter::Type::BLUR, {10, 10});
    sleep(1);
}

TEST(StreamerTest, misuseStreamer) {

    Streamer my_streamer(0);

    //stop without starting
    bool caught = false;
    try {
        my_streamer.stopDisplay();
    }
    catch(std::exception& e) {
        std::cout << "caught " << e.what() << std::endl;
        caught = true;
    }

    EXPECT_TRUE(caught);

    //start twice
    caught = false;
    my_streamer.startDisplay("valid");
    sleep(1);
    try {
        my_streamer.startDisplay("invalid");
    }
    catch(std::exception& e) {
        std::cout << "caught " << e.what() << std::endl;
        caught = true;
    }
    EXPECT_TRUE(caught);
}


