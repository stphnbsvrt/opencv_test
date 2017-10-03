#include "streamer.hpp"

Streamer::Streamer(int device) :
  m_vc(device),
  m_frame(cv::imread(std::string(_SOURCE_DIR_) + std::string("/common/streamer/streamer_default.png"))),
  m_continue_stream(true),
  m_continue_display(false) {

    //make sure we have a videocapture, then start reading it to our display image
    if(false == m_vc.isOpened()) {
        throw std::runtime_error("Couldn't open streamer");
    }

    startStream();
}

Streamer::Streamer(const std::string& filename) :
  m_vc(filename),
  m_frame(cv::imread(std::string(_SOURCE_DIR_) + std::string("/common/streamer/streamer_default.png"))),
  m_continue_stream(true),
  m_continue_display(false) {

    //make sure we have a videocapture, then start reading it to our display image
    if(false == m_vc.isOpened()) {
        throw std::runtime_error("Couldn't open streamer");
    }

    startStream();
}

Streamer::~Streamer() {
    if(nullptr != m_display_thread) {
       stopDisplay();
    }
    stopStream();
}

void Streamer::startStream() {
    m_stream_thread = std::make_unique<std::thread>(&Streamer::stream, this);
}

void Streamer::stream() {
    try {
        while(true == m_continue_stream) {
            updateStreamFrame();
        }
    }
    catch(...) {

        //report exception after we've joined
        m_stream_exception = std::current_exception();
    }
}

void Streamer::updateStreamFrame() {
    cv::Mat tmp_frame;
    m_vc.read(tmp_frame);
    m_filter.applyTo(tmp_frame);
    m_frame = tmp_frame;
}

void Streamer::stopStream() {

    m_continue_stream = false;
    m_stream_thread->join();
    m_stream_thread = nullptr;

    //check for caught exceptions
    if(nullptr != m_stream_exception) {
        try {
            std::rethrow_exception(m_stream_exception);
        }
        catch(std::exception& e) {
            m_stream_exception = nullptr;
            throw std::runtime_error(std::string(e.what()) + " - Streamer failed!");
        }
    }
}

void Streamer::startDisplay(std::string&& window_name) {

    //one at a time
    if(nullptr != m_display_thread) {
        throw std::runtime_error("Trying to start display while thread is already running");
    }

    //start display thread
    m_display_name = window_name;
    m_continue_display = true;
    m_display_thread = std::make_unique<std::thread>(&Streamer::Display, this);
}

void Streamer::Display() {

    //no exceptions allowed
    try {
        while(true == m_continue_display) {
            showDisplay();
        }
    }
    catch(...) {

        //rethrow after we've joined
        m_display_exception = std::current_exception();
    }
}

void Streamer::showDisplay() {
    cv::imshow(m_display_name, m_frame);
    //TODO: this should be configurable
    cv::waitKey(5);
}

void Streamer::stopDisplay() {

    if(nullptr == m_display_thread) {
        throw std::runtime_error("Invalid stopDisplay()");
    }

    //send stop signal, join, then destory the thread
    m_continue_display = false;
    m_display_thread->join();
    m_display_thread = nullptr;
    cv::destroyWindow(m_display_name);

    //check for caught exceptions
    if(nullptr != m_display_exception) {
        try {
            std::rethrow_exception(m_display_exception);
        }
        catch(std::exception& e) {
            m_display_exception = nullptr;
            throw std::runtime_error(std::string(e.what()) + "Display error caught!");
        }
    }
}
