#include <iostream>
#include <opencv2/opencv.hpp>
#include <kfbreader_Dll.h>
#include <time.h>
using namespace std;
using namespace cv;

/*��ȡkfb��ʽͼ���roi*/
cv::Mat readRoi(std::string path, int roi_start_x, int roi_start_y, int roi_width, int roi_height)
{
	int w = 0;
	int h = 0;
	int scale = 20;

	kfbreader reader;
	reader.ReadInfo(path, scale, w, h, 1);
	unsigned char* data = nullptr;
	reader.ReadRoi(roi_start_x, roi_start_y, roi_width, roi_height, scale, &data);

	Mat ROI(roi_width, roi_height, CV_8UC3, data);
	return ROI;
}
/*��ʾroi*/
void show(string winName, cv::Mat image)
{
	cv::imshow(winName, image);
	cv::waitKey(0);
}
/*������˹�����㷽��*/
double isImageValid(cv::Mat img)
{
	cv::Mat matImageGray;
	cv::cvtColor(img, matImageGray, CV_BGR2GRAY);

	cv::Mat dst;
	cv::Laplacian(matImageGray, dst, CV_16S, 3);//3�Ǹ�˹�˴�С

	cv::Mat tmp_m, tmp_sd; //��ֵ  ��׼��
	cv::meanStdDev(dst, tmp_m, tmp_sd);
	double m = 0, sd = 0;
	m = tmp_m.at<double>(0, 0);
	sd = tmp_sd.at<double>(0, 0);
	return sd * sd;
}

int main(void)
{
	clock_t start;
	clock_t end;
	string path = "E://180491-PLA2R_2018-06-19 15_46_25.kfb";
	
	/*��ȡ����kfbͼ��*/
	kfbreader kfb;
	int w = 0;
	int h = 0;
	kfb.ReadInfo(path, 20, w, h, 1);
	cout <<"ͼ��ߴ�Ϊ��"<< "w: " << w << " " << "h��" << h << endl;
	cout << "ʶ����...." << endl;

	/*�ֳ�2000*2000�����ɸ���Ұ*/
	int numVision_w = w / 1000 ;
	int numVision_h = h / 1000 ;
	double score = 0;
	double threshold = 5000;
	int cnt_valid = 0;  //��Ч���������
	int cnt_invalid = 0; //��Ч���������
	
	/*����ָ��ROIѰ�Һ�����ֵ 5839
	
	
	cv::Mat roi3 = readRoi(path, 5500, 19000, 1000, 1000);
	cout << isImageValid(roi3) << endl;
	show("roi", roi3);
	*/

	/*��ʼִ��ʶ�𲿷�*/
	
	start = clock();
	for (int i = 0;i < numVision_w; ++i)
	{
		for (int j = 0;j < numVision_h; ++j)
		{
			cv::Mat roi = readRoi(path, i * 2000, j * 2000, 2000, 2000);
			score = isImageValid(roi);
			std::string result = (score > threshold) ? "True" : "False";
			if (score >= threshold)
			{
				cnt_valid++; 
			}
			else
			{
				cnt_invalid++;
			}
			//std::cout << "Score: " << int(score) << "--->" << result << "\t";
		}
		//cout << endl;
	}
	end = clock();

	std::cout << "����Ϊ" << numVision_w * numVision_h << "����Ұ" << endl;
	std::cout << "��Ч��Ұ�У�" << cnt_valid << "��" << endl;
	std::cout << "��Ч��Ұ�У�" << cnt_invalid << "��" << endl;
	double time = (double)(end - start) / CLOCKS_PER_SEC; 
	std::cout << "ʶ����ʱΪ��" << time << "��" << endl;
	std::cout << "ÿ����Ұʶ��ʱ��Ϊ��" << time / (numVision_w * numVision_h) * 1000 << "ms" << endl;
	return 0;
}