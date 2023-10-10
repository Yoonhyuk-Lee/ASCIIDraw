#include <Windows.h>
#include <iterator>

#include "opencv2\opencv.hpp"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range2d.h"

#include "MyImage.h"
#include "ASCIIConvertLUT.hpp"

static ASCIIConvertLUT<256> ASCIIMap;
static const cv::Ptr<cv::CLAHE> pCLAHE = cv::createCLAHE(4.);

using namespace tbb;

void MyImage::AnisotropicDiffusion(const cv::Mat& src, cv::Mat& dst)
{
	cv::imshow("ori", src);
	cv::waitKey(1);

	const int W = src.cols;
	const int H = src.rows;

	PBYTE pbSrc = src.data;
	PBYTE pbTmp = new BYTE[W * H]{ 0, };
	PBYTE pbDst = dst.data;
	
	AnisotropicDiffusion(pbSrc, pbDst, W, H, 24);
	for (int i = 0; i < 20; ++i)
	{
		AnisotropicDiffusion(pbDst, pbTmp, W, H, 24);
		AnisotropicDiffusion(pbTmp, pbDst, W, H, 24);
	}
	delete[] pbTmp;

	cv::imshow("anisotropic", dst);
	cv::waitKey(1);
}

void MyImage::ResizeAndAdjustImage(const cv::Mat& src, cv::Mat& dst, cv::Size&& size)
{
	cv::resize(src, dst, size);
	cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
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

	cv::imshow("draw", src);
	cv::waitKey(1);
}

void MyImage::AnisotropicDiffusion(PBYTE pbSrc, PBYTE pbDst, const int nWidth, const int nHeight, const float fK)
{
	const float K_SQR = fK * fK;

	parallel_for(blocked_range2d<int, int>(1, nHeight - 1, 1, nWidth - 1), [&](const blocked_range2d<int, int>& r)
		{
			for (int j = r.rows().begin(); j < r.rows().end(); ++j)
			{
				const int J_OFFSET = j * nWidth;
				for (int i = r.cols().begin(); i < r.cols().end(); ++i)
				{
					const int CURR = i + J_OFFSET;
					
					const int CUR_VAL = pbSrc[CURR];

					const int dN = pbSrc[CURR - nWidth] - CUR_VAL;
					const int dE = pbSrc[CURR + 1] - CUR_VAL;
					const int dW = pbSrc[CURR - 1] - CUR_VAL;
					const int dS = pbSrc[CURR + nWidth] - CUR_VAL;

					const float corrN = K_SQR / (K_SQR + dN * dN);
					const float corrE = K_SQR / (K_SQR + dE * dE);
					const float corrW = K_SQR / (K_SQR + dW * dW);
					const float corrS = K_SQR / (K_SQR + dS * dS);

					int nTmp = corrN * dN + corrE * dE + corrW * dW + corrS * dS;

					pbDst[CURR] = std::min(std::max(CUR_VAL + nTmp / 12, 0), 255);
				}
			}
		});
}
