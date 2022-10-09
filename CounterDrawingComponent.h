//
// Created by kacper on 08.10.22.
//

#ifndef JUGGLINGFIRST_COUNTERDRAWINGCOMPONENT_H
#define JUGGLINGFIRST_COUNTERDRAWINGCOMPONENT_H
#include "DrawingComponent.h"

class CounterDrawingComponent : public DrawingComponent {
public:
    CounterDrawingComponent(int low_line_position, int min_ball_area,
                            int max_ball_area, int high_line_position);
    void update(Counter &counter, std::vector<std::vector<cv::Point>> &contours) override;
private:
    const int low_line_position;
    const int min_ball_area;
    const int max_ball_area;
    const int high_line_position;
    cv::RNG rng;
};


#endif //JUGGLINGFIRST_COUNTERDRAWINGCOMPONENT_H
