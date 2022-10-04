#ifndef JUGGLINGFIRST_INPUTREADER_H
#define JUGGLINGFIRST_INPUTREADER_H


#include <string>
#include <boost/program_options.hpp>
#include <opencv2/videoio.hpp>
#include "ColorPicker.h"

namespace po = boost::program_options;


class InputReader {
public:
    InputReader(int argc, char** argv);
    int get_balls_number() const;
    std::string get_balls_image_dir();
    std::string get_balls_video_dir();
    std::string get_output_dir();
    bool is_markers() const;
    std::vector<cv::Vec3b> get_colors();
private:
    std::vector<cv::Vec3b> colors;
    void read_colors(cv::Mat &);
    po::options_description options;
    cv::VideoCapture balls_image;
    int balls_number;
    std::string balls_image_dir;
    std::string balls_video_dir;
    std::string output_dir;
    bool markers;
    std::string window_name;
};


#endif //JUGGLINGFIRST_INPUTREADER_H
