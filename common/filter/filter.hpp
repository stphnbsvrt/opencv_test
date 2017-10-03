#ifndef _FILTER_HPP_
#define _FILTER_HPP_

#include <memory>
#include <opencv2/opencv.hpp>

class Filter {

public:

    ///
    /// \brief Enumeration of filter types
    ///
    
    enum class Type {

        ///
        /// \brief Normalized box filter
        ///
        /// \args[0] blurring kernel width
        /// \args[1] blurring kernel height
        ///

        BLUR = 0
    };

    ///
    /// \brief Default constructor, filter does nothing
    ///

    Filter();

    ///
    /// \brief Destructor
    ///

    ~Filter();

    ///
    /// \brief Apply filter to image
    ///
    /// \param[in/out] image Image to filter
    ///

    void applyTo(cv::Mat& image);

    ///
    /// \brief Add a filter to apply
    /// Multiple filters will be applied in order
    ///
    /// \param[in] type Type of filter to add
    /// \param[in] args List of uint32_t args
    /// Interpretation of args defined by type
    ///

    //TODO: better way to pass variable args
    void addFilter(Type type, std::vector<uint32_t> args);

protected:

    ///
    /// \brief List of added filters to apply to images
    ///

    std::vector<std::pair<Type, std::vector<uint32_t>>> m_filters;

};

#endif //_FILTER_HPP_
