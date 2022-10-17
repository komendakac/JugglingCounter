//
// Created by kacper on 08.10.22.
//

#ifndef JUGGLINGFIRST_COUNTER_H
#define JUGGLINGFIRST_COUNTER_H
#include <opencv2/opencv.hpp>
#include "IsolatorComponent.h"
#include "CountingComponent.h"
#include "DrawingComponent.h"
#include <memory>


class IsolatorComponent;
class DrawingComponent;
class CountingComponent;

class Counter {
public:
    Counter(std::shared_ptr<IsolatorComponent> isolatorComponent,
            std::shared_ptr<CountingComponent> countingComponent,
            std::shared_ptr<DrawingComponent> drawingComponent, unsigned balls_number);
    void update(cv::Mat &frame);
    unsigned frames_since_start;
    int dequeue_size;
    int counter;
    cv::Mat base_frame;
    cv::Mat current_frame;
    std::deque<std::vector<std::pair<int, int>>> balls_positions;
    unsigned balls_number;
private:
    std::shared_ptr<IsolatorComponent> isolatorComponent;
    std::shared_ptr<CountingComponent> countingComponent;
    std::shared_ptr<DrawingComponent> drawingComponent;
};


#endif //JUGGLINGFIRST_COUNTER_H
