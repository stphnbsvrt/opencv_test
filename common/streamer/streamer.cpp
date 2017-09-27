#include "streamer.hpp"

Streamer::Streamer(int device) :
  m_vc(device),
  m_continue_stream(true),
  m_continue_display(false) {

    //make sure we have a videocapture, then start reading it to our display image
    if(false == m_vc.isOpened()) {
        throw std::runtime_error("Couldn't open streamer");
    }

    startStream();
}

Streamer::Streamer(const std::string& filename) :
    m_vc(filename) {}

Streamer::~Streamer() {
    stopStream();
}

void Streamer::startStream() {
    m_stream_thread = std::make_unique<std::thread>(&Streamer::stream, this);
}

void Streamer::stream() {
    try {
        while(true == m_continue_stream) {
            m_vc.read(m_display_frame);
        }
    }
    catch(...) {

        //report exception after we've joined
        m_stream_exception = std::current_exception();
    }
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
            std::cerr << "Caught: " << e.what() << " during display thread execution!" << std::endl;
            m_stream_exception = nullptr;
            std::cerr << "Streamer failed!" << std::endl;
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
            cv::imshow(m_display_name, m_display_frame);
            //TODO: this should be configurable
            cv::waitKey(5);
        }
    }
    catch(...) {

        //rethrow after we've joined
        m_display_exception = std::current_exception();
    }
}

void Streamer::stopDisplay() {

    //send stop signal, join, then destory the thread
    m_continue_display = false;
    m_display_thread->join();
    m_display_thread = nullptr;

    //check for caught exceptions
    if(nullptr != m_display_exception) {
        try {
            std::rethrow_exception(m_display_exception);
        }
        catch(std::exception& e) {
            std::cerr << "Caught: " << e.what() << " during display thread execution!" << std::endl;
            m_display_exception = nullptr;
            throw std::runtime_error("Display error caught!");
        }
    }
}
