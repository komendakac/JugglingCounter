//
// Created by kacper on 08.10.22.
//

#include "Counter.h"


Counter::Counter(std::shared_ptr<IsolatorComponent> isolatorComponent,
                 std::shared_ptr<CountingComponent> countingComponent,
                 std::shared_ptr<DrawingComponent> drawingComponent, unsigned balls_number) :
            frames_since_start(0), counter(0), dequeue_size(0),
            countingComponent(std::move(countingComponent)),
            drawingComponent(std::move(drawingComponent)),
            isolatorComponent(std::move(isolatorComponent)),
            balls_number(balls_number) {
    for (int i = 0; i < 3; i++) {
        balls_positions.emplace_back(std::vector<std::pair<int, int>>());
    }
}


void Counter::update(cv::Mat &frame) {
    frames_since_start++;
    base_frame = frame;
    isolatorComponent ->update(*this, frame);
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(current_frame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    countingComponent ->update(*this, contours);

    drawingComponent ->update(*this, contours);
}