#include <thread>
#include <opencv2/opencv.hpp>
#include "filter.hpp"

#ifndef _STREAMER_HPP_
#define _STREAMER_HPP_

///
/// \brief Wrapper for VideoCapture class to capture a camera stream
/// Planned benefits: option to show frames in window while other operations are being performed
///

class Streamer {
    
public:

    ///
    /// \brief Constructor taking camera index
    ///

    Streamer(int device);

    ///
    /// \brief Constructor taking filename
    ///

    Streamer(const std::string& filename);

    ///
    /// \brief Destructor
    ///

    ~Streamer();

    ///
    /// \brief Show the stream in a window
    ///
    /// \param[in] window_name Name of the window
    ///

    void startDisplay(std::string&& window_name);

    ///
    /// \brief Stop the display thread
    /// Throws exception if error was detected during display

    void stopDisplay();

    ///
    /// \brief Add a filter to apply
    /// Multiple filters will be applied in order
    ///
    /// \param[in] type Type of filter to add
    /// \param[in] args List of uint32_t args
    /// Interpretation of args defined by type
    ///

    void addFilter(Filter::Type type, std::vector<uint32_t> args) { m_filter.addFilter(type, args); };

protected:

    ///
    /// \brief Function to start reading images from our stream
    ///

    void startStream();

    ///
    /// \brief Threaded function for reading stream images
    ///

    void stream();

    ///
    /// \brief Virtual function to update the next frame
    ///

    virtual void updateStreamFrame();

    ///
    /// \brief Stop reading images from stream
    ///

    void stopStream();

    ///
    /// \brief Display function to show our current image
    ///

    void Display();

    ///
    /// \brief Virtual function for how to show the display
    ///

    virtual void showDisplay();

    ///
    /// \brief Underlying video source
    ///

    cv::VideoCapture m_vc;

    ///
    /// \brief Filter to apply to images from source
    ///

    Filter m_filter;

    ///
    /// \brief Latest frame from stream
    ///

    cv::Mat m_frame;

    //////////////////////////////////////////////////////////////
    // Stream() member variables
    //////////////////////////////////////////////////////////////

    ///
    /// \brief Thread for reading our stream
    ///

    std::unique_ptr<std::thread> m_stream_thread;

    ///
    /// \brief Used to tell stream thread when to stop execution
    ///

    bool m_continue_stream;

    ///
    /// \brief Used to save an exception from the stream thread
    ///

    std::exception_ptr m_stream_exception;

    ///////////////////////////////////////////////////////////////
    // Display() member variables
    ///////////////////////////////////////////////////////////////

    ///
    /// \brief Thread for running our display
    ///

    std::unique_ptr<std::thread> m_display_thread;

    ///
    /// \brief Name to use for the display
    ///

    std::string m_display_name;

    ///
    /// \brief Flag to tell display thread to stop execution
    ///

    bool m_continue_display;

    ///
    /// \brief Used to save an exception from the display thread
    ///

    std::exception_ptr m_display_exception;

};

#endif //_STREAMER_HPP_
