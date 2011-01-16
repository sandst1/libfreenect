#include "optflow.h"

#include "cv.h"
#include <highgui.h>

#include "hist_segment.h"

static CvMat* optflow_prev = NULL;
static CvMat* optflow_velx = NULL;
static CvMat* optflow_vely = NULL;

#define BLOCK_SIZE cvSize(8,8)
#define SHIFT_SIZE cvSize(2,2)
#define MAX_RANGE  cvSize(4,4)

void optflow_init(CvSize size)
{
    optflow_prev = cvCreateMat(size.height, size.width, CV_8UC1);
    CvSize velsize = cvSize((size.width - BLOCK_SIZE.width)/SHIFT_SIZE.width,
                            (size.height-BLOCK_SIZE.height)/SHIFT_SIZE.width);

    optflow_velx = cvCreateMat(velsize.height, velsize.width, CV_32F);
    optflow_vely = cvCreateMat(velsize.height, velsize.width, CV_32F);

    cvNamedWindow("optflow", CV_WINDOW_NORMAL);
}

void optflow_deinit()
{
    cvReleaseMat(&optflow_prev);
    cvReleaseMat(&optflow_velx);
    cvReleaseMat(&optflow_vely);
    cvDestroyWindow("optflow");
}

void optflow_calculate(CvMat* input, CvMat* output)
{
    cvZero(optflow_velx);
    cvZero(optflow_vely);

    cvCalcOpticalFlowBM(optflow_prev, input, BLOCK_SIZE, SHIFT_SIZE, MAX_RANGE, 0, optflow_velx, optflow_vely);

    cvShowImage("optflow", optflow_velx);


    // Take the current frame into optflow_prev
    cvCopy(input, optflow_prev, NULL);

}

