#include "stepdetector.h"
#include <cmath>
#include <stdio.h>

unsigned int steps = 0;

StepDetector::StepDetector(QObject *parent) :
    QObject(parent)
{
}
#define STANDARD_GRAVITY 9.80665

#define H 480
float   mLimit = 10;
float   mLastValue = 0;
float   mScale = - (H * 0.5f * (1.0f / (STANDARD_GRAVITY * 2)));
float   mYOffset = H * 0.5f;

float   mLastDirection = 0;
float   mLastExtremes[2];
float   mLastDiff = 0;
int     mLastMatch = -1;

bool StepDetector::filter(QAccelerometerReading *reading)
{
    float values[3];

    values[0] = reading->x();
    values[1] = reading->y();
    values[2] = reading->z();

    float vSum = 0;
    for (int i=0 ; i<3 ; i++) {
        float v = mYOffset + values[i] * mScale;
        vSum += v;
    }

    float v = vSum / 3;

    float direction = (v > mLastValue ? 1 : (v < mLastValue ? -1 : 0));
    if (direction == - mLastDirection) {
      // Direction changed
      int extType = (direction > 0 ? 0 : 1); // minumum or maximum?
      mLastExtremes[extType] = mLastValue;
      float diff = fabs(mLastExtremes[extType] - mLastExtremes[1 - extType]);

      if (diff > mLimit) {
            bool isAlmostAsLargeAsPrevious = diff > (mLastDiff*2/3);
            bool isPreviousLargeEnough = mLastDiff > (diff/3);
            bool isNotContra = (mLastMatch != 1 - extType);

            if (isAlmostAsLargeAsPrevious && isPreviousLargeEnough && isNotContra) {
                emit stepDetected();

                mLastMatch = extType;
            }
            else {
                mLastMatch = -1;
            }
        }
        mLastDiff = diff;
    }
    mLastDirection = direction;
    mLastValue = v;

    return false;
}
