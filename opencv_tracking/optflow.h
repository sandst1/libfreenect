#ifndef OPTICAL_FLOW_CALC_H
#define OPTICAL_FLOW_CALC_H

#include <cv.h>

void optflow_init(CvSize size);
void optflow_deinit();

void optflow_calculate(CvMat* input, CvMat* output);

#endif
