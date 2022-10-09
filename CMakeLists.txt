cmake_minimum_required(VERSION 3.23)
project(jugglingfirst)

set(CMAKE_CXX_STANDARD 14)

add_executable(jugglingfirst main.cpp ColorPicker.cpp ColorPicker.h InputReader.cpp InputReader.h
        CounterIsolatorComponent.cpp CounterIsolatorComponent.h IsolatorComponent.h IsolatorComponent.cpp
        CounterCountingComponent.cpp CounterCountingComponent.h  CountingComponent.h
        CounterDrawingComponent.cpp CounterDrawingComponent.h  DrawingComponent.h
        Counter.h Counter.cpp)



find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp)
include_directories(${OpenCV_INCLUDE_DIRS})
FIND_PACKAGE( Boost 1.71 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES})