#include "hist_segment.h"

#include <highgui.h>

#define CV_WHITE CV_RGB(255,255,255)

#define HISTOGRAM_BINS 256

static CvHistogram* histogram = NULL;
static IplImage*    histogram_image = NULL;
static float        histogram_minval = 0.0;
static float        histogram_maxval = 0.0;
void hist_segment_init()
{
    int bins = HISTOGRAM_BINS;
    int hsize[] = {bins};

    float xranges[] = { 0, 255 };
    float* ranges[] = { xranges };

    cvNamedWindow("histogram", CV_WINDOW_NORMAL);

    histogram = cvCreateHist( 1, hsize, CV_HIST_ARRAY, ranges, 1);
    histogram_image = cvCreateImage(cvSize(bins, 500), 8, 1);
}

void hist_segment_deinit()
{
    cvDestroyWindow("histogram");
    cvReleaseHist(&histogram);
    cvReleaseImage(&histogram_image);
}

void hist_segment(CvMat* input, CvMat* output)
{
    int i = 0;
    float val = 0.0;
    int normalized = 0;
    // Reset the histogram image
    cvZero(histogram_image);

    // Calculate the histogram
    cvCalcHist(&input, histogram, 0, NULL);

    cvGetMinMaxHistValue(histogram, &histogram_minval, &histogram_maxval, NULL, NULL );

    //printf("histmax: %.2f\n", histogram_maxval);

    // Draw the histogram
    for( i=0; i < HISTOGRAM_BINS; i++ )
    {
        val = cvQueryHistValue_1D( histogram, i );
        normalized = cvRound(val*500/histogram_maxval);
        cvLine(histogram_image, cvPoint(i,500), cvPoint(i,500-normalized), CV_WHITE, 1, 8, 0);
    }

    cvShowImage("histogram", histogram_image);

}
