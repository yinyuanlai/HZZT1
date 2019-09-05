///*TCTͼ��ģ����� �հ������ų�����*/
//#include<iostream>
//#include<time.h>
//#include<opencv/cv.hpp>
//#include <kfbreader_Dll.h>
//using namespace std;
//using namespace cv;
///*
//��ȡkfb��ʽͼ���roi
//param1  path           kfb·��
//param2  roi_start_x    ͼ�����ϽǺ�����
//param3  roi_start_y    ͼ�����Ͻ�������
//param4  roi_width      ͼ����
//param5  roi_height     ͼ��߶�
//*/
//cv::Mat readRoi(std::string path, int roi_start_x, int roi_start_y, int roi_width, int roi_height)
//{
//	int w = 0, h = 0;
//	int scale = 10; //�Ŵ���
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
//��ʾͼ��
//param1 winName  ������
//param2 image    ͼ������
//*/
//void show(string winName, Mat image)
//{
// 	cv::imshow(winName, image);
//	cv::waitKey(0);
//}
//
///*
//����ͼ��
//param1  img    �������ͼ��
//param2  s  ���ű���
//*/
//void Resize(cv::Mat &img, double scale)
//{
//	Size dsize = Size(img.cols * scale, img.rows * scale);
//	cv::resize(img, img, dsize);
//}
///*��ģ����Ұ��*/
//cv::Mat sharpen2D(const Mat& image, Mat& result)
//{
//	// ���ȹ���һ���ں�
//	Mat kernel(3, 3, CV_32F, Scalar(0));
//	// ��Ӧ�ں˽��и�ֵ
//	kernel.at<float>(1, 1) = 5.0;
//	kernel.at<float>(0, 1) = -1.0;
//	kernel.at<float>(2, 1) = -1.0;
//	kernel.at<float>(1, 0) = -1.0;
//	kernel.at<float>(1, 2) = -1.0;
//	// ��ͼ������˲�����
//	filter2D(image, result, image.depth(), kernel);
//	return result;
//}
///*
//ϸ������
//param1  img   ����ͼ��
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
//	cout << "��Ч��������:" << count << endl;
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