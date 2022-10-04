#include "ColorPicker.h"

void ColorPicker::getMouseCoordinates(int event, int x, int y, int flags, void *param) {
    if (event == cv::EVENT_LBUTTONDOWN){
        ((ColorPicker*)param) -> x = x;
        ((ColorPicker*)param) -> y = y;
    }
}


void ColorPicker::show_coordinates() const {
    std::cout << x << " " << y << '\n';
}


ColorPicker::ColorPicker(cv::Mat *image) : x(0), y(0){
    this->image = image;
}


cv::Vec3b ColorPicker::get_color() {
    cv::Mat image_hsv;
    cv::cvtColor(*image, image_hsv, cv::COLOR_BGR2HSV);
    color = image_hsv.at<cv::Vec3b>(cv::Point(x, y));
    return color;
}
