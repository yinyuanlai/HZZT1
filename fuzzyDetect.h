#pragma once
#ifdef DLL_API
#else
#define DLL_API_declspec(dllexport)
#endif
#include <opencv2/opencv.hpp>
#include<string>
/*��ȡkfb��ʽͼ���roi*/
cv::Mat readRoi(std::string path, int roi_start_x, int roi_start_y, int roi_width, int roi_height);
/*��ʾroi*/
void show(std::string winName, cv::Mat image);
/*������˹�����㷽��*/
double isImageValid(cv::Mat img)
