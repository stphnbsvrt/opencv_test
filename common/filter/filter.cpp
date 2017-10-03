#include "filter.hpp"

Filter::Filter() {}

Filter::~Filter() {}

void Filter::applyTo(cv::Mat& image) {

    for(auto it = m_filters.begin(); it != m_filters.end(); it++) {
        switch(it->first) {
            
            case Filter::Type::BLUR:
                cv::blur(image, image, cv::Size(it->second[0], it->second[1]));
                break;
        }
    }
}

void Filter::addFilter(Filter::Type type, std::vector<uint32_t> args) {

    switch(type) {

        case Filter::Type::BLUR:
            if(2 != args.size()) {
                throw std::runtime_error("Bad args for BLUR filter");
            }
            m_filters.push_back({type, args});
            break;
        default:
            std::cerr << "Unrecognized filter specified" << std::endl;
            throw std::runtime_error("Unrecognized filter");

    }
}
