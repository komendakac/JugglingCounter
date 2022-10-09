//
// Created by kacper on 08.10.22.
//

#ifndef JUGGLINGFIRST_ISOLATORCOMPONENT_H
#define JUGGLINGFIRST_ISOLATORCOMPONENT_H


#include "Counter.h"

class Counter;

class IsolatorComponent {
public:
    virtual ~IsolatorComponent() = default;
    virtual void update(Counter &counter, cv::Mat &frame) = 0;
};


#endif //JUGGLINGFIRST_ISOLATORCOMPONENT_H
