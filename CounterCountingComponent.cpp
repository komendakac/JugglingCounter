//
// Created by kacper on 08.10.22.
//

#include "CounterCountingComponent.h"

CounterCountingComponent::CounterCountingComponent(const int low_line_position, const int min_ball_area,
                                                   const int max_ball_area, const int high_line_position)
                                                   : contours_number(0), low_line_position(low_line_position),
                                                   min_ball_area(min_ball_area), max_ball_area(max_ball_area),
                                                   high_line_position(high_line_position){

}

void CounterCountingComponent::update(Counter &counter, std::vector<std::vector<cv::Point>> &contours) {
    std::vector<std::pair<int, int>> centroids;
     contours_number = 0;
    for (auto &contour : contours) {
        if (cv::contourArea(contour) >= min_ball_area && cv::contourArea(contour) <= max_ball_area) {
            cv::Moments moments;
            moments = cv::moments(contour);
            int avg_x = static_cast<int>(moments.m10 / moments.m00);
            int avg_y = static_cast<int>(moments.m01 / moments.m00);

            if (avg_y > high_line_position){
                double area = cv::contourArea(contour);
                contours_number++;

                centroids.emplace_back(std::make_pair(avg_x, avg_y));
            }
        }
    }
    if (contours_number == counter.balls_number){
        counter.balls_positions.emplace_back(centroids);
        counter.balls_positions.pop_front();
        if (counter.dequeue_size <= 3)
            counter.dequeue_size++;
        else  {
            int new_counted = count_balls(counter.balls_positions);
            counter.counter += new_counted;
        }
    }
}

int CounterCountingComponent::count_balls(std::deque<std::vector<std::pair<int, int>>> balls_positions){
    auto current = balls_positions.begin();
    auto previous = current;
    previous++;
    auto last = previous;
    last++;
    int counted_balls = 0;
    for (auto element : *last){
        std::pair<int, int> closest_of_curr;
        std::pair<int, int> closest_of_prev;
        for (unsigned i = 0; i < (*previous).size(); i++){
            if (count_distance(element, (*previous)[i]) <
                count_distance(closest_of_prev, element)) {
                closest_of_prev = (*previous)[i];
            }
            if (count_distance(element, (*current)[i]) <
                count_distance(closest_of_curr, element)) {
                closest_of_curr = (*current)[i];
            }
        }
        if (element.second < low_line_position &&
            closest_of_prev.second > low_line_position &&
            closest_of_curr.second > low_line_position){
            counted_balls++;
        }
        closest_of_prev = std::make_pair(-100, -100);
        closest_of_curr = std::make_pair(-100, -100);
    }
    return counted_balls;
}

double CounterCountingComponent::count_distance(std::pair<int, int> first, std::pair<int, int> second){
    if (first.first == -1 || second.first == -1){
        return DBL_MAX;
    }
    return sqrt(pow(first.first - second.first, 2) + pow(first.second- second.second, 2));
}

