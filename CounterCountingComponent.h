//
// Created by kacper on 08.10.22.
//

#ifndef JUGGLINGFIRST_COUNTERCOUNTINGCOMPONENT_H
#define JUGGLINGFIRST_COUNTERCOUNTINGCOMPONENT_H
#include "CountingComponent.h"

class CounterCountingComponent : public CountingComponent{
public:
    CounterCountingComponent(int low_line_position, int min_ball_area,
                             int max_ball_area, int high_line_position);
    void update(Counter &counter, std::vector<std::vector<cv::Point>> &contours) override;
private:
    unsigned contours_number;
    int count_balls(std::deque<std::vector<std::pair<int, int>>>);
    static double count_distance(std::pair<int, int>&, std::pair<int, int>&);
    static void set_closer(std::pair<int, int> &first, std::pair<int, int> &second,
                                              std::pair<int, int> &current);
    void count_if_crossed_line(const int &current,const int &previous,
                               const int &third, const int &line_position, int &counter) const;
    const int low_line_position;
    const int min_ball_area;
    const int max_ball_area;
    const int high_line_position;
};


#endif //JUGGLINGFIRST_COUNTERCOUNTINGCOMPONENT_H
