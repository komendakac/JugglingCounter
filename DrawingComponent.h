//
// Created by kacper on 08.10.22.
//

#ifndef JUGGLINGFIRST_DRAWINGCOMPONENT_H
#define JUGGLINGFIRST_DRAWINGCOMPONENT_H


#include "Counter.h"

class Counter;

class DrawingComponent {
public:
    virtual ~DrawingComponent() = default;
    virtual void update(Counter &counter, std::vector<std::vector<cv::Point>> &contours) = 0;
};


#endif //JUGGLINGFIRST_DRAWINGCOMPONENT_H
