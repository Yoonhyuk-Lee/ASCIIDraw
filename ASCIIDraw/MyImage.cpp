#include "opencv2\opencv.hpp"

#include "MyImage.h"
#include "ASCIIConverter.h"


MyImage::MyImage(const std::string& filePath)
{
	m_pSrc = new cv::Mat(cv::imread(filePath, cv::IMREAD_GRAYSCALE));

	cv::equalizeHist(*m_pSrc, *m_pSrc);
}

MyImage::~MyImage()
{
	if (m_pSrc != nullptr)
	{
		delete m_pSrc;
		m_pSrc = nullptr;
	}
}

void MyImage::DrawImage()
{
	if (m_pSrc == nullptr)
		return;

	const int W = m_pSrc->cols;
	const int H = m_pSrc->rows;

	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			float val = m_pSrc->at<uchar>(y, x) / 255.f;
			printf("%c", ASCIIConverter::norm2ASCII(val));
		}
		printf("\n");
	}
}