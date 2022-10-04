#include "InputReader.h"


InputReader::InputReader(int argc, char** argv): options("Allowed options"), balls_number(3),
                                                    balls_image_dir(std::string()),  balls_video_dir(std::string()),
                                                    markers(false), window_name("Pick color"){
    options.add_options()
            ("help", "produce help message")
            ("balls,b", po::value<int>(&balls_number)->default_value(3))
            ("image_directory,i", po::value<std::string>(&balls_image_dir))
            ("video_directory,v", po::value<std::string>(&balls_video_dir))
            ("output_directory,o", po::value<std::string>(&output_dir)->default_value(""));
            ("enable_markers", po::bool_switch(&markers) ->default_value(false));

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, options), vm);
    po::notify(vm);

    balls_image.open(balls_image_dir);
    if( !balls_image.isOpened() ) { // check if we succeeded
        //std::cerr << "Couldn't open capture." << std::endl;
        //TODO exception handling
        throw "can't read image";
    }
    cv::Mat image;
    balls_image >> image;
    read_colors(image);
}


int InputReader::get_balls_number() const {
    return balls_number;
}


std::string InputReader::get_balls_image_dir() {
    return balls_image_dir;
}


std::string InputReader::get_balls_video_dir() {
    return balls_video_dir;
}


bool InputReader::is_markers() const {
    return markers;
}


void InputReader::read_colors(cv::Mat &frame){
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);// Create a window for display.
    ColorPicker cp(&frame);
    cv::imshow(window_name, frame);
    cv::setMouseCallback(window_name, ColorPicker::getMouseCoordinates, &cp);
    cv::Mat frame_hsv;
    cv::cvtColor(frame, frame_hsv, cv::COLOR_BGR2HSV);
    for (int i = 0; i < balls_number; i++) {
        cv::waitKey(0);
        cv::Vec3b color_hsv = cp.get_color();
        colors.emplace_back(color_hsv);
    }
    cv::destroyWindow(window_name);
}


std::vector<cv::Vec3b> InputReader::get_colors() {
    return colors;
}


std::string InputReader::get_output_dir() {
    return output_dir;
}
