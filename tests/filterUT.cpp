#include "main.hpp"
#include "filter.hpp"

TEST(FilterTest, Default) {

    //construct default
    auto filter = std::make_shared<Filter>();
    cv::Mat image = cv::imread(std::string(_SOURCE_DIR_) + std::string("/common/streamer/streamer_default.png"));
    cv::Mat initial_image = image.clone();

    filter->applyTo(image);

    EXPECT_EQ(0, cv::countNonZero(initial_image != image));

}

TEST(FilterTest, Smoothing) {

    auto blur_filter = std::make_shared<Filter>();
    cv::Mat image = cv::imread(std::string(_SOURCE_DIR_) + std::string("/common/streamer/streamer_default.png"));
    cv::imshow("before filter", image);
    cv::waitKey(1000);
    cv::destroyWindow("before filter");

    blur_filter->addFilter(Filter::Type::BLUR, {40, 40});
    blur_filter->applyTo(image);
    cv::imshow("after filter", image);
    cv::waitKey(1000);
    cv::destroyWindow("after filter");
}

