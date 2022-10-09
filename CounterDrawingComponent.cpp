//
// Created by kacper on 08.10.22.
//

#include "CounterDrawingComponent.h"
#include <iostream>


void CounterDrawingComponent::update(Counter &counter, std::vector<std::vector<cv::Point>> &contours) {
    std::vector<std::vector<cv::Point> >hull( contours.size() );
    for( size_t i = 0; i < contours.size(); i++ ){
        convexHull( contours[i], hull[i] );
    }
    cv::Size s = counter.base_frame.size();
    cv::Mat drawing = cv::Mat::zeros(s, CV_8UC3 );

    int image_width = static_cast<int>(s.width);

    cv::line(drawing,
             cv::Point(0, low_line_position),
             cv::Point(image_width, low_line_position),
             cv::Scalar(255, 0, 0),
             1);
    cv::Mat modified_frame = counter.base_frame;
    for( size_t i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 256),
                                       rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, hull, static_cast<int>(i), color );
        drawContours( modified_frame, hull, static_cast<int>(i), color );

    }
    for (auto &contour : contours) {

        if (cv::contourArea(contour) >= min_ball_area && cv::contourArea(contour) <= max_ball_area) {
            cv::Moments moments;
            moments = cv::moments(contour);
            int avg_x = static_cast<int>(moments.m10 / moments.m00);
            int avg_y = static_cast<int>(moments.m01 / moments.m00);

            if (avg_y > high_line_position) {
                std::stringstream stream;
                stream << avg_x << ',' << avg_y;
                std::string text;
                stream >> text;
                cv::putText(drawing, text, cv::Point(avg_x + 25, avg_y + 25),
                            cv::FONT_HERSHEY_SIMPLEX, 0.3,
                            cv::Scalar(255, 0, 0));
                cv::putText(modified_frame, text, cv::Point(avg_x + 25, avg_y + 25),
                            cv::FONT_HERSHEY_SIMPLEX, 0.3,
                            cv::Scalar(255, 0, 0));
                cv::Rect rectangle = cv::boundingRect(contour);
                cv::rectangle(drawing, rectangle, cv::Scalar(255, 0, 0), 2);
                cv::rectangle(modified_frame, rectangle, cv::Scalar(255, 0, 0), 2);
            }
        }
    }
    cv::putText(drawing, std::to_string(counter.counter), cv::Point(100, 400),
                cv::FONT_HERSHEY_SIMPLEX, 5, cv::Scalar(255, 0,0));


    cv::Mat concat;
    cv::hconcat(modified_frame, drawing, concat);
    cv::imshow("Display window", concat);
    cv::waitKey(1);
}

CounterDrawingComponent::CounterDrawingComponent(const int low_line_position, const int min_ball_area,
                                                 const int max_ball_area, const int high_line_position) :
                                                 low_line_position(low_line_position), min_ball_area(min_ball_area),
                                                 max_ball_area(max_ball_area), high_line_position(high_line_position),
                                                 rng(12345){

}
