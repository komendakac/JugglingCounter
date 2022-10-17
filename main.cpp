#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "InputReader.h"
#include "CounterIsolatorComponent.h"
#include "CounterCountingComponent.h"
#include "CounterDrawingComponent.h"
#include <memory>


const int low_line_position = 800;
const int min_ball_area = 350;
const int max_ball_area = 3500;
const int high_line_position = 0;



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


    std::vector<cv::Vec3b> colors = input.get_colors();
    std::shared_ptr<IsolatorComponent> isolator = std::make_shared<CounterIsolatorComponent>(colors);
    std::shared_ptr<CountingComponent> counting = std::make_shared<CounterCountingComponent>(low_line_position,
                                                                                             min_ball_area,
                                                                                             max_ball_area,
                                                                                             high_line_position);
    std::shared_ptr<DrawingComponent> drawing = std::make_shared<CounterDrawingComponent>(low_line_position,
                                                                                          min_ball_area,
                                                                                          max_ball_area,
                                                                                          high_line_position);
    Counter counter(isolator, counting, drawing,
                    input.get_balls_number());

    while (!frame.empty()) {
        counter.update(frame);

        cap >> frame;

    }
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
