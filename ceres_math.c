#ifndef INCLUDE_CERES_MATH
#define CERES_MATH

#include <stdint.h>

#define CERES_MAX(a, b) (a < b ? b : a)
#define CERES_MIN(a, b) (a < b ? a : b)
#define CERES_SQR(a) ((a) * (a))
#define CERES_SQRT_DIST(x1, y1, x2, y2) (CERES_SQR(x1 - x2) + CERES_SQR(y1 - y2))
#define CERES_SIGNOF(x) (x < 0 ? -1 : 1)
#define CERES_ABS(x) (CERES_SIGNOF(x) * x)

#ifdef CERES_MATH_USE
#define Ceres_Lerp	__CeresMath_Lerp
#endif

float __CeresMath_Lerp(int x1, int x2, float t) {
	return (1 - t) * x2 + t * x1;
}

#endif
