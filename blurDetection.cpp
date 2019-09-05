#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <kfbreader_Dll.h>
using namespace std;
using namespace cv;
//读取kfb格式图像的roi
cv::Mat readRoi(std::string path,int roi_start_x, int roi_start_y,int roi_width,int roi_height)
{
	int w = 0, h = 0, scale = 10; //scale 放大倍数

	kfbreader reader;
	reader.ReadInfo(path, scale, w, h, 1);
	unsigned char *data = nullptr;
	reader.ReadRoi(roi_start_x, roi_start_y, roi_width,roi_height,scale, &data);

	Mat ROI(roi_width, roi_height, CV_8UC3, data);
	return ROI;
}

//显示ROI
void show(string winName,Mat image)
{
	imshow(winName,image);
	waitKey(0);
}

/*
细胞计数
param1  img   输入图像
*/
int countCell(cv::Mat &img)
{

	cv::Mat gray;
	cv::cvtColor(img, gray, COLOR_BGR2GRAY);

	cv::Mat binary;
	threshold(gray, binary, 127, 255, THRESH_BINARY);

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	cv::findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	double area = 0;
	int count = 0;
	for (int i = 0; i < contours.size(); ++i)
	{
		auto cnt = contours[i];
		area = cv::contourArea(cnt);
		if (area >= 85)
		{
			count++;
		}
	}
	return count;
}
/*
cv::Mat sharpen2D(const Mat& image)
{
	// 首先构造一个内核
	Mat kernel(3, 3, CV_32F, Scalar(0));
	// 对应内核进行赋值
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;
	// 对图像进行滤波操作
	filter2D(image, image, image.depth(), kernel);
	return image;
}
*/
//laplacian
double isImageBlurry(cv::Mat &img)
{
	cv::Mat matImageGray;
	cv::cvtColor(img, matImageGray, CV_BGR2GRAY);

	cv::Mat dst;
	cv::Laplacian(matImageGray, dst, CV_16S, 3);//3是高斯核大小

	cv::Mat tmp_m, tmp_sd; //均值  标准差
	cv::meanStdDev(dst, tmp_m, tmp_sd);
	double m = 0, sd = 0;
	m = tmp_m.at<double>(0, 0);
	sd = tmp_sd.at<double>(0, 0);

	int threshold = 900; //设置阈值 

	std::string result = (sd * sd > threshold) ? "清晰" : "模糊";
	std::cout << "识别结果：" << result << std::endl;
	return sd * sd;
}

int main(void)
{
	std::string path = "E:/kfb/bad/12.kfb";
	
	//获取中间ROI start_x = 0,start_y=15000 height=2000,width=32000
	kfbreader kfb;
	int w = 0, h = 0;
	kfb.ReadInfo(path, 10, w, h, 1);

	double num = w / 2048; //视野个数 
	cout << "=============================================图像信息=============================================" << endl;
	cout << "图像大小：" << w << "*" << h << endl;
	cout << "选取视野个数：" << " " << num << endl;
	cout << "=============================================识别结果=============================================" << endl;

	clock_t startTime; //程序开始执行时间
	clock_t endTime;   //程序执行完的时间
	double costTime;   //识别程序耗时

	//std::vector<cv::Mat> ROIS;
	startTime = clock();
	for (int i = 0;i < num;i++)
	{
		cv::Mat roi = readRoi(path, i * 2048, w / 2 - 1024, 2048, 2048); //path,x,y,w,h
		if (countCell(roi) > 100)
		{
			double score = isImageBlurry(roi);
		}
		else
		{
			cout << "识别结果：" << "模糊" << endl;
		}
			
	}
	endTime = clock();
	costTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	cout << "=============================================识别耗时=============================================" << endl;
	cout << "识别程序用时：" << costTime << "s" << endl;
	cout << "每个视野识别用时：" << costTime / num * 1000 << "ms" << endl;
}



