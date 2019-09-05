///*TCT图像模糊检测 空白区域排除试验*/
//#include<iostream>
//#include<time.h>
//#include<opencv/cv.hpp>
//#include <kfbreader_Dll.h>
//using namespace std;
//using namespace cv;
///*
//读取kfb格式图像的roi
//param1  path           kfb路径
//param2  roi_start_x    图像左上角横坐标
//param3  roi_start_y    图像左上角纵坐标
//param4  roi_width      图像宽度
//param5  roi_height     图像高度
//*/
//cv::Mat readRoi(std::string path, int roi_start_x, int roi_start_y, int roi_width, int roi_height)
//{
//	int w = 0, h = 0;
//	int scale = 10; //放大倍数
//
//	kfbreader reader;
//	reader.ReadInfo(path, scale, w, h, 1);
//	unsigned char* data = nullptr;
//	reader.ReadRoi(roi_start_x, roi_start_y, roi_width, roi_height, scale, &data);
//
//	Mat ROI(roi_width, roi_height, CV_8UC3, data);
//	return ROI;
//}
//
///*
//显示图像
//param1 winName  窗口名
//param2 image    图像数据
//*/
//void show(string winName, Mat image)
//{
// 	cv::imshow(winName, image);
//	cv::waitKey(0);
//}
//
///*
//缩放图像
//param1  img    输入输出图像
//param2  s  缩放倍数
//*/
//void Resize(cv::Mat &img, double scale)
//{
//	Size dsize = Size(img.cols * scale, img.rows * scale);
//	cv::resize(img, img, dsize);
//}
///*真模糊视野锐化*/
//cv::Mat sharpen2D(const Mat& image, Mat& result)
//{
//	// 首先构造一个内核
//	Mat kernel(3, 3, CV_32F, Scalar(0));
//	// 对应内核进行赋值
//	kernel.at<float>(1, 1) = 5.0;
//	kernel.at<float>(0, 1) = -1.0;
//	kernel.at<float>(2, 1) = -1.0;
//	kernel.at<float>(1, 0) = -1.0;
//	kernel.at<float>(1, 2) = -1.0;
//	// 对图像进行滤波操作
//	filter2D(image, result, image.depth(), kernel);
//	return result;
//}
///*
//细胞计数
//param1  img   输入图像
//*/
//cv::Mat countCell(cv::Mat img)
//{
//	
//	cv::Mat gray;
//	cv::cvtColor(img, gray, COLOR_BGR2GRAY);
//
//	cv::Mat binary;
//	threshold(gray, binary, 127, 255, THRESH_BINARY);
//	
//	std::vector<std::vector<Point>> contours;
//	std::vector<Vec4i> hierarchy;
//	cv::findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
//	double area = 0;
//	int count = 0;
//	for (int i = 0; i < contours.size(); ++i)
//	{
//		auto cnt = contours[i];
//		area = cv::contourArea(cnt);
//		if (area >= 100)
//		{
//			count++;
//		}
//		
//	}
//	cout << "有效轮廓个数:" << count << endl;
//	return binary;
//}
//
//int main(void)
//{
//	std::string path = "E:/kfb/bad/59.kfb";
//	kfbreader kfb;
//	int w = 0, h = 0;
//	kfb.ReadInfo(path, 10, w, h, 1);
//	double num = w / 2048;
//	for (int i = 0; i < num; i++)
//	{
//		cv::Mat roi = readRoi(path, i * 2048, w / 2 - 1024, 2048, 2048); //path,x,y,w,h
//		countCell(roi);
//	}
//	
//}