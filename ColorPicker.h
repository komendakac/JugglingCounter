#ifndef JUGGLINGFIRST_COLORPICKER_H
#define JUGGLINGFIRST_COLORPICKER_H
#include <opencv2/opencv.hpp>


class ColorPicker {
    int x;
    int y;
    cv::Mat *image; //should be given as HSV
    cv::Vec3b color;
public:
    explicit ColorPicker(cv::Mat *image);
    static void getMouseCoordinates(int event, int x, int y, int flags, void* param);
    void show_coordinates() const;
    cv::Vec3b get_color();
};


#endif //JUGGLINGFIRST_COLORPICKER_H
