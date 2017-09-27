#include <iostream>
#include <opencv2/opencv.hpp>

main(int argc, char* argv[]) {

    cv::VideoCapture cam_stream;
    uint32_t device_idx;
    std::cout << "Device idx: ";
    std::cin >> device_idx;

    cam_stream.open(device_idx);
    if(false == cam_stream.isOpened()) {
        throw std::runtime_error("Failed to open stream at device idx " + std::to_string(device_idx));
    }

    cv::Mat frame;
    for(;;) {
        cam_stream.read(frame);
        if(frame.empty()) {
            std::cerr << "Blank frame grabbed" << std::endl;
        }

        cv::imshow("Live", frame);
        if(cv::waitKey(5) >= 0) {
                break;
        }
    }
}
