#include "classifier.hpp"

Classifier::Classifier(int device_idx, std::string prototxt, std::string caffe_model, std::string id_class_map) 
: Streamer(device_idx),
  m_network(cv::dnn::readNetFromCaffe(prototxt, caffe_model)),
  m_classes(readClasses(id_class_map))
{}

Classifier::Classifier(const std::string& filename, std::string prototxt, std::string caffe_model, std::string id_class_map)
: Streamer(filename),
  m_network(cv::dnn::readNetFromCaffe(prototxt, caffe_model)),
  m_classes(readClasses(id_class_map))
{}

Classifier::~Classifier() {
}


void Classifier::updateStreamFrame() {

    Streamer::updateStreamFrame();
}

void Classifier::showDisplay() {

    //classify the image
    cv::Mat net_input = cv::dnn::blobFromImage(m_frame, 1, cv::Size(224, 224), cv::Scalar(104, 117, 123));
    cv::Mat prob;
    cv::TickMeter t;
    for(int i = 0; i < 10; i++) {
        CV_TRACE_REGION("forward");
        m_network.setInput(net_input, "data");
        t.start();
        prob = m_network.forward("prob");
        t.stop();
    }
    int classId;
    double classProb;
    cv::Mat prob_mat = prob.reshape(1, 1);
    cv::Point class_number;
    cv::minMaxLoc(prob_mat, NULL, &classProb, NULL, &class_number);
    classId = class_number.x;

    std::cout << "Best class: " << m_classes.at(classId) << " " << classProb * 100 << "%" << std::endl;
    Streamer::showDisplay();
}

//from docs.opencv.org/3.3.0/d5/de7/tutorial_dnn_googlenet.html
std::vector<std::string> Classifier::readClasses(std::string class_file) {

    std::vector<std::string> ret_vec;

    std::ifstream fp(class_file);
    if(!fp.is_open()) {
        std::cerr << "File with classes labels not found: " << class_file << std::endl;
        throw std::runtime_error("Bad class file");
    }

    std::string name;
    while(!fp.eof()) {
        std::getline(fp, name);
        if(name.length()) {
            ret_vec.push_back(name.substr(name.find(' ')+1));
        }
    }
    fp.close();
    return ret_vec;
}



