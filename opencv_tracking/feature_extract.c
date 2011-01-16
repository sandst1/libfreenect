#include "feature_extract.h"

#include <highgui.h>

static CvMat* feature_image = NULL;

void feature_extract_init()
{
    feature_image = cvCreateMat(480, 640, CV_8UC1);
    cvNamedWindow("featureImage", CV_WINDOW_NORMAL);
}

void feature_extract_deinit()
{
    cvReleaseMat(&feature_image);
    cvDestroyWindow("featureImage");
}

//void cvExtractSURF(const CvArr* image, const CvArr* mask, CvSeq** keypoints, CvSeq** descriptors, CvMemStorage* storage, CvSURFParams params)¶

void extractFeatures(CvMat* input)
{
    cvCopy(input, feature_image, NULL);
    int i = 0;
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* keypoints = NULL;

    cvGetStarKeypoints( input, storage, cvStarDetectorParams(45,30,10,8,5));
/*
    for ( i = 0; i < (keypoints ? keypoints->total : 0); i++ )
    {
        CvStarKeypoint point = *(CvStarKeypoint*)cvGetSeqElem(keypoints, i);
        int r = point.size/2;
        cvCircle(feature_image, point.pt, 15, cvScalarAll(255), 1, 8, 0);
    }
*/
    cvShowImage("featureImage", feature_image);

}
