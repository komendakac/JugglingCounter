#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "InputReader.h"
#include "CounterIsolatorComponent.h"
#include "CounterCountingComponent.h"
#include "CounterDrawingComponent.h"

cv::RNG rng(12345);
static int low_line_position = 800;
static int min_ball_area = 350;
static int max_ball_area = 3500;
static int high_line_position = 0;

/*int count_balls(std::deque<std::vector<std::pair<int, int>>>);
double count_distance(std::pair<int, int>, std::pair<int, int>);*/


int main(int argc, char** argv) {
    InputReader input(argc, argv);

    std::string video_dir = input.get_balls_video_dir();
    cv::VideoCapture cap;
    cap.open(video_dir);
    std::string output = input.get_output_dir();

    if( !cap.isOpened() ) { // check if we succeeded
        std::cerr << "Couldn't open capture." << std::endl;
        return -1;
    }

    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);

    cv::Mat frame;
    cap >> frame;

    //std::deque<std::vector<std::pair<int, int>>> balls_positions;
    /*unsigned balls_number = input.get_balls_number();

    for (int i = 0; i < 3; i++) {
        balls_positions.emplace_back(std::vector<std::pair<int, int>>());
    }
    int counter = 0;*/

    std::vector<cv::Vec3b> colors = input.get_colors();
    Counter counter(new CounterIsolatorComponent(colors),
                    new CounterCountingComponent(low_line_position, min_ball_area,
                                                 max_ball_area, high_line_position),
                    new CounterDrawingComponent(low_line_position, min_ball_area,
                                                max_ball_area, high_line_position),
                    input.get_balls_number());
    /*unsigned frames_since_start = 0;
    int dequeue_size = 0;*/
    while (!frame.empty()) {
        counter.update(frame);
        /*frames_since_start++;

        cv::Mat threshold_image = isolator.get_isolated_balls(frame);

        std::vector<std::vector<cv::Point> > contours;
        cv::findContours(threshold_image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        std::vector<std::vector<cv::Point> >hull( contours.size() );
        for( size_t i = 0; i < contours.size(); i++ ){
            convexHull( contours[i], hull[i] );
        }

        cv::Mat drawing = cv::Mat::zeros(threshold_image.size(), CV_8UC3 );

        int image_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));

        cv::line(drawing,
                 cv::Point(0, low_line_position),
                 cv::Point(image_width, low_line_position),
                 cv::Scalar(255, 0, 0),
                 1);
        cv::Mat modified_frame = frame;
        for( size_t i = 0; i< contours.size(); i++ )
        {
            cv::Scalar color = cv::Scalar( rng.uniform(0, 256),
                                           rng.uniform(0,256), rng.uniform(0,256) );
            drawContours( drawing, hull, static_cast<int>(i), color );
            drawContours( modified_frame, hull, static_cast<int>(i), color );

        }

        unsigned contours_number = 0;
        std::vector<std::pair<int, int>> centroids;
        for (auto &contour : contours) {

            if (cv::contourArea(contour) >= min_ball_area && cv::contourArea(contour) <= max_ball_area) {
                cv::Moments moments;
                moments = cv::moments(contour);
                int avg_x = static_cast<int>(moments.m10 / moments.m00);
                int avg_y = static_cast<int>(moments.m01 / moments.m00);

                if (avg_y > high_line_position){
                    contours_number++;

                    centroids.emplace_back(std::make_pair(avg_x, avg_y));
                    std::stringstream stream;
                    stream << avg_x << ',' << avg_y;
                    std::string text;
                    stream >> text;
                    cv::putText(drawing, text, cv::Point(avg_x + 25, avg_y + 25),
                                cv::FONT_HERSHEY_SIMPLEX, 0.3,
                                cv::Scalar(255, 0,0 ));
                    cv::putText(modified_frame, text, cv::Point(avg_x + 25, avg_y + 25),
                                cv::FONT_HERSHEY_SIMPLEX, 0.3,
                                cv::Scalar(255, 0,0 ));
                    cv::Rect rectangle = cv::boundingRect(contour);
                    cv::rectangle(drawing, rectangle, cv::Scalar(255, 0, 0), 2);
                    cv::rectangle(modified_frame, rectangle, cv::Scalar(255, 0, 0), 2);
                }
            }
        }
        if (contours_number == balls_number){
            balls_positions.emplace_back(centroids);
            balls_positions.pop_front();
            if (dequeue_size <= 3)
                dequeue_size++;
            else  {
                int new_counted = count_balls(balls_positions);
                counter += new_counted;
            }
        }

        cv::putText(drawing, std::to_string(counter), cv::Point(100, 400),
                    cv::FONT_HERSHEY_SIMPLEX, 5, cv::Scalar(255, 0,0));


        cv::Mat concat;
        cv::hconcat(modified_frame, drawing, concat);*/
        cap >> frame;

        //cv::imshow("Display window", concat);

        //cv::waitKey(1);
    }
    cap.release();
    cv::destroyAllWindows();

    return 0;
}

/*int count_balls(std::deque<std::vector<std::pair<int, int>>> balls_positions){
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
            if (count_distance(element, (*previous)[i]) < count_distance(closest_of_prev, element)) {
                closest_of_prev = (*previous)[i];
            }
            if (count_distance(element, (*current)[i]) < count_distance(closest_of_curr, element)) {
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

double count_distance(std::pair<int, int> first, std::pair<int, int> second){
    if (first.first == -1 || second.first == -1){
        return DBL_MAX;
    }
    return sqrt(pow(first.first - second.first, 2) + pow(first.second- second.second, 2));
}*/
