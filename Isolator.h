#ifndef JUGGLINGFIRST_ISOLATOR_H
#define JUGGLINGFIRST_ISOLATOR_H
#include <opencv2/opencv.hpp>


class Isolator {
public:
    explicit Isolator(std::vector<cv::Vec3b> colors);
    cv::Mat get_isolated_balls(const cv::Mat& picture);

private:
    std::vector<cv::Vec3b> colors;
    static int get_upper_bound(int color, int max = 255);
    static int get_lower_bound(int color);
};


#endif //JUGGLINGFIRST_ISOLATOR_H
