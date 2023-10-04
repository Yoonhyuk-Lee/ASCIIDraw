#include <Windows.h>

#include "opencv2\opencv.hpp"

#include "MyImage.h"
#include "ASCIIConvertLUT.hpp"

static ASCIIConvertLUT<256> ASCIIMap;
static const cv::Ptr<cv::CLAHE> pCLAHE = cv::createCLAHE(4.);

void MyImage::ResizeAndAdjustImage(const cv::Mat& src, cv::Mat& dst, cv::Size&& size)
{
	cv::resize(src, dst, size);
	cv::cvtColor(dst, dst, cv::COLOR_BGR2GRAY);
	pCLAHE->apply(dst, dst);
}

void MyImage::DrawImage(const cv::Mat& src)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

	const int W = src.cols;
	const int H = src.rows;

	std::string line;
	line.assign(W, ' ');
	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			line[x] = ASCIIMap.LUT[src.at<uchar>(y, x)];
		}
		std::cout << line << std::endl;
	}
}
