//
// Created by kacper on 08.10.22.
//

#ifndef JUGGLINGFIRST_COUNTINGCOMPONENT_H
#define JUGGLINGFIRST_COUNTINGCOMPONENT_H

#include "Counter.h"

class Counter;

class CountingComponent {
public:
    virtual ~CountingComponent() = default;
    virtual void update(Counter &counter, std::vector<std::vector<cv::Point>> &contours) = 0;
};


#endif //JUGGLINGFIRST_COUNTINGCOMPONENT_H
