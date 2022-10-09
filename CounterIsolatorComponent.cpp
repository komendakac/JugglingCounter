//
// Created by kacper on 04.10.22.
//

#include "CounterIsolatorComponent.h"

#include <utility>
const int hsv_range = 32;

int CounterIsolatorComponent::get_upper_bound(int color, int max){
    return color + hsv_range > max ? max : color + hsv_range;
}


int CounterIsolatorComponent::get_lower_bound(int color){
    return color - hsv_range < 0 ? 0 : color - hsv_range;
}


cv::Mat CounterIsolatorComponent::get_isolated_balls(const cv::Mat& picture) {
    cv::Mat picture_hsv;

    cv::cvtColor(picture, picture_hsv, cv::COLOR_BGR2HSV);
    std::vector<cv::Mat> frames_threshold;
    for (auto & threshold_color : colors) {
        int hl = get_lower_bound(threshold_color[0]);
        int sl = get_lower_bound(threshold_color[1]);
        int vl = get_lower_bound(threshold_color[2]);
        int hu = get_upper_bound(threshold_color[0], 179);
        int su = get_upper_bound(threshold_color[1]);
        int vu = get_upper_bound(threshold_color[2]);

        cv::Mat frame_threshold;
        cv::inRange(picture_hsv,
                    cv::Scalar(hl, sl, vl),
                    cv::Scalar(hu, su, vu),
                    frame_threshold);
        frames_threshold.emplace_back(frame_threshold);
    }

    cv::Mat mask = frames_threshold[0];
    for (int i = 1; i < frames_threshold.size(); i++){
        cv::Mat new_mask;
        cv::bitwise_or(mask, frames_threshold[i], new_mask);
        mask = new_mask;
    }
    cv::Mat balls;
    cv::bitwise_and(picture_hsv, picture_hsv, balls, mask);
    int morph_size = 5;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_CROSS,
                                               cv::Size(morph_size * 2 + 1, morph_size * 2 + 1),
                                               cv::Point(morph_size, morph_size));

    cv::Mat opened;
    cv::morphologyEx(balls, opened, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 2);
    cv::Mat dilated;
    cv::morphologyEx(opened, dilated, cv::MORPH_DILATE, kernel, cv::Point(-1, -1), 2);
    cv::Mat eroded;
    cv::morphologyEx(dilated, eroded, cv::MORPH_ERODE, kernel, cv::Point(-1, -1), 1);
    cv::Mat threshold_image;
    cv::Mat hsv_channels[3];
    cv::split( eroded, hsv_channels );
    cv::threshold(hsv_channels[2], threshold_image, 120, 255, cv::THRESH_BINARY);
    return threshold_image;
}


CounterIsolatorComponent::CounterIsolatorComponent(std::vector<cv::Vec3b> colors) : colors(std::move(colors)){
}


void CounterIsolatorComponent::update(Counter &counter, cv::Mat &frame) {
    counter.current_frame = get_isolated_balls(frame);
}
