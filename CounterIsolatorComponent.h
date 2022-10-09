#ifndef JUGGLINGFIRST_COUNTERISOLATORCOMPONENT_H
#define JUGGLINGFIRST_COUNTERISOLATORCOMPONENT_H
#include <opencv2/opencv.hpp>
#include "IsolatorComponent.h"


class CounterIsolatorComponent : public IsolatorComponent{
public:
    explicit CounterIsolatorComponent(std::vector<cv::Vec3b> colors);
    cv::Mat get_isolated_balls(const cv::Mat& picture);
    void update(Counter &counter, cv::Mat &frame);

private:
    std::vector<cv::Vec3b> colors;
    static int get_upper_bound(int color, int max = 255);
    static int get_lower_bound(int color);
};


#endif //JUGGLINGFIRST_COUNTERISOLATORCOMPONENT_H