#ifndef FEATURE_EXTRACT_H
#define FEATURE_EXTRACT_H

#include <cv.h>

void feature_extract_init();
void feature_extract_deinit();

void extractFeatures(CvMat* input);

#endif
