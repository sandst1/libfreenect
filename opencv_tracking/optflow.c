#include "optflow.h"

#include <highgui.h>

static CvMat* optflow_prev = NULL;
static CvMat* optflow_velx = NULL;
static CvMat* optflow_vely = NULL;

void optflow_init(CvSize size)
{
    optflow_prev = cvCreateMat(size.height, size.width, CV_8UC1);
    optflow_velx = cvCreateMat(size.height, size.width, CV_32F);
    optflow_vely = cvCreateMat(size.height, size.width, CV_32F);

    cvNamedWindow("optflow_velx", CV_WINDOW_NORMAL);
    cvNamedWindow("optflow_vely", CV_WINDOW_NORMAL);
}

void optflow_deinit()
{
    cvReleaseMat(&optflow_prev);
    cvReleaseMat(&optflow_velx);
    cvReleaseMat(&optflow_vely);

    cvDestroyWindow("optflow_velx");
    cvDestroyWindow("optflow_vely");
}

void optflow_calculate(CvMat* input, CvMat* output)
{
    cvZero(optflow_velx);
    cvZero(optflow_vely);

    // void cvCalcOpticalFlowHS(const CvArr* prev, const CvArr* curr, int usePrevious, CvArr* velx, CvArr* vely, double lambda, CvTermCriteria criteria)

    cvCalcOpticalFlowHS(optflow_prev, input, 0, optflow_velx, optflow_vely, 0.1, cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3 ));

    cvShowImage("optflow_velx", optflow_velx);
    cvShowImage("optflow_vely", optflow_vely);

    // Take the current frame into optflow_prev
    cvCopy(input, optflow_prev, NULL);

}

