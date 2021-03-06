#pragma once
#include <qobject.h>
#include <iostream>
#include <iomanip> 
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <thread>
#include <atomic>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <opencv2/opencv.hpp>            // C++
#include "opencv2/core/version.hpp"

extern cv::Mat mat;
extern int fps;
extern int carnum;
extern int carcount;
extern int traffic_density;
extern bool stopornot;
extern float ave_carspeed;
extern cv::Mat mat;
extern int fps;
extern int carnum;
extern int carcount;
extern int traffic_density;
extern double car_speed;
extern unsigned int car_id;
//extern int car_flow;
extern bool timer_start;
class yolo_console_dll: public QObject
{
	Q_OBJECT

public:
	yolo_console_dll();
	int startyolo();
	~yolo_console_dll();
	void update(cv::Mat frame,int current_cap_fps);
	int i;
	void updatetime();

signals:
	void updatemat();
};

