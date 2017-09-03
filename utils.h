#pragma once

#include <cmath>

#define DEG_TO_RAD 0.017453f
#define PI 3.141592654f
#define PI2 (PI * 2)

#define FLOAT_EPSILON 0.0001f //부동소수점 오차로 일어날 수 있는 최소값

namespace MY_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);

	float getAngle(float x1, float y1, float x2, float y2);
}

