#include "fgStreamer.hpp"

FGStreamer::FGStreamer(int device_idx, int type) 
: Streamer(device_idx) {
    m_bg_sub = createBackgroundSubtractor(type);
}

FGStreamer::FGStreamer(const std::string& filename, int type)
: Streamer(filename) {
    m_bg_sub = createBackgroundSubtractor(type);
}

FGStreamer::~FGStreamer() {
}

cv::Ptr<cv::BackgroundSubtractor> FGStreamer::createBackgroundSubtractor(int type) {

    cv::Ptr<cv::BackgroundSubtractor> bg_sub;
    switch(type) {
        case 0:
            bg_sub = cv::createBackgroundSubtractorMOG2();
            break;
        case 1:
            bg_sub = cv::createBackgroundSubtractorKNN();
            break;
        default:
            std::cerr << "Unrecognized background subtractor type: " << type << std::endl;
            throw std::runtime_error("Unrecognized background subtractor type");
    }
    return bg_sub;
}

void FGStreamer::updateStreamFrame() {

    Streamer::updateStreamFrame();
    if(nullptr != m_bg_sub) {
        m_bg_sub->apply(m_frame, m_fg_mask);
    }
}

void FGStreamer::showDisplay() {

    cv::imshow(m_display_name, m_frame);
    cv::imshow("Foreground", m_fg_mask);
    cv::waitKey(5);
}
