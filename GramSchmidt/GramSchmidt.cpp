// GramSchmidt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <string.h>

void GramSchmidt(const CvMat *src,CvMat *dst)
{
	int i, j;
	double param1, param2, param;
	assert(src != NULL&&dst != NULL);
	assert(src->cols == dst->cols&&dst->rows == dst->rows);
	CvMat *VecSrc = cvCreateMat(1, src->rows, CV_64FC1);
	CvMat *VecDst = cvCreateMat(1, dst->rows, CV_64FC1);
	CvMat *VecTmp = cvCreateMat(1, dst->rows, CV_64FC1);
	cvZero(VecSrc);
	cvZero(VecDst);
	for ( i = 0; i < dst->rows; i++)
	{
		cvGetRow(src, VecSrc, i);
		cvGetRow(src, VecDst, i);
		for (j = 0;j < i;++j)
		{
			cvGetRow(dst, VecTmp, j);
			param1 = cvDotProduct(VecSrc, VecTmp);
			param2 = cvDotProduct(VecDst, VecTmp);
			param = param1 / param2;
			cvAddWeighted(VecTmp, -param, VecDst, 1.0, 0, VecDst);
		}
		memcpy(dst->data.db + i*dst->cols, VecDst->data.db, dst->cols*sizeof(double));
	}
	cvReleaseMat(&VecSrc);
	cvReleaseMat(&VecDst);
	cvReleaseMat(&VecTmp);
}


int _tmain(int argc, _TCHAR* argv[])
{
	CvMat *Ma, *Mb;
	int i, j;
	Ma = cvCreateMatHeader(3, 4, CV_64FC1);
	Mb = NULL;
	const double a[] = {1,0,1,1,
				0,1,1,0,
				0,0,1,1};
	cvInitMatHeader(Ma, 3, 4, CV_64FC1, (void*)a);
	Mb = cvCreateMat(Ma->rows, Ma->cols, CV_64FC1);
	
	return 0;
}

