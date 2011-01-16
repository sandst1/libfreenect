#ifndef SEGMENT_HIST_H
#define SEGMENT_HIST_H

#include <cv.h>
void hist_segment_init();

void hist_segment_deinit();

void hist_segment(CvMat* input, CvMat* output);

#endif
