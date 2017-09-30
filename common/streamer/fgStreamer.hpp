#include "streamer.hpp"

///
/// \brief Only show foreground features when streaming
///

class FGStreamer : public Streamer {

public:

    ///
    /// \brief Construct using camera index
    ///
    /// \param[in] device_idx Camera index
    /// \param[in] type Type of background subtractor to use
    ///

    FGStreamer(int device_idx, int type);

    ///
    /// \brief Construct using filename
    ///
    /// \param[in] filename Name of the camera file to open
    /// \param[in] type Type of background subtractor to use
    ///

    FGStreamer(const std::string& filename, int type);

    ///
    /// \brief Destructor
    ///

    ~FGStreamer();

protected:

    ///
    /// \brief FGStreamer read next video frame
    ///

    virtual void updateStreamFrame() override;

    ///
    /// \brief FGStreamer show current frame
    ///

    virtual void showDisplay() override;

    ///
    /// \brief Create a background subtractor based on type
    ///
    /// \param[in] type Type of background subtractor
    ///
    /// \return Pointer to new background subtractor
    ///
    
    static cv::Ptr<cv::BackgroundSubtractor> createBackgroundSubtractor(int type);

    ///
    /// \brief Pointer to our background subtractor
    ///

    cv::Ptr<cv::BackgroundSubtractor> m_bg_sub;

    ///
    /// \brief Pointer to our fg output
    ///

    cv::Mat m_fg_mask;

};
