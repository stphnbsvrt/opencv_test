#ifndef _CLASSIFIER_HPP_
#define _CLASSIFIER_HPP_

#include <opencv2/dnn.hpp>
#include <opencv2/core/utils/trace.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "streamer.hpp"


///
/// \brief Show a description of what is in the stream
///

class Classifier : public Streamer {

public:

    ///
    /// \brief Construct using camera index
    ///
    /// \param[in] device_idx Camera index
    /// \param[in] prototxt Name of prototxt file with network architecture desc.
    /// \param[in] caffeModel Name of the caffemodel file containing a learned network
    /// \param[in] idClassMap Map of returned ids to names of possible classifications
    ///

    Classifier(int device_idx, std::string prototxt, std::string caffeModel, std::string idClassMap);

    ///
    /// \brief Construct using filename
    ///
    /// \param[in] filename Name of the camera file to open
    /// \param[in] prototxt Name of prototxt file with network architecture desc.
    /// \param[in] caffeModel Name of the caffemodel file containing a learned network
    /// \param[in] idClassMap Map of returned ids to names of possible classifications
    ///

    Classifier(const std::string& filename, std::string prototxt, std::string caffeModel, std::string idClassMap);

    ///
    /// \brief Destructor
    ///

    ~Classifier();

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
    /// \brief Read classes from an input file
    ///

    std::vector<std::string> readClasses(std::string class_file); 

    ///
    /// \brief This classifier's network
    ///

    cv::dnn::Net m_network;

    ///
    /// \brief Interpretation of returned class Ids, mapped by index in vector
    ///

    std::vector<std::string> m_classes;
};

#endif //_CLASSIFIER_HPP_
