#ifndef _MATHS_H_
#define _MATHS_H_

#include <stdlib.h>
#include <math.h>

namespace maths
{
	// Random
	
	inline int randi (int max) { return rand() % max; }
	inline int randi (int min, int max) { return (rand() % (max - min)) + min; }
	
	inline float randf () { return (rand() % 10000) / 10000.0f; }
	inline float randf (float max) { return randf() * max; }
	inline float randf (float min, float max) { return randf() * (max - min) + min; }
	
	// angles
	
	inline float angleDiff (float a, float b) {
		float diff = a - b;
		
		while (diff > M_PI) { diff -= 2*M_PI; }
		while (diff < -M_PI) { diff += 2*M_PI; }
		
		return diff;
	}
	
	// Lerp
	
	inline float lerp (float t, float a, float b) {
		return a+((b-a)*t);
	}
	
	// min/max/clamp
	
	template <typename T>
	inline T min (T a, T b) {
		return (a < b) ? a : b;
	}
	
	template <typename T>
	inline T max (T a, T b) {
		return (a > b) ? a : b;
	}
	
	template <typename T>
	inline T clamp (T v, T minVal, T maxVal) {
		return min(max(v, minVal), maxVal);
	}
	
	// min/max of 3 elements
	
	template <typename T>
	inline T min (T a, T b, T c) {
		return min(a, min(b, c));
	}
	
	template <typename T>
	inline T max (T a, T b, T c) {
		return max(a, max(b, c));
	}
	
	// min/max of 4 elements
	
	template <typename T>
	inline T min (T a, T b, T c, T d) {
		return min(a, min(b, c, d));
	}
	
	template <typename T>
	inline T max (T a, T b, T c, T d) {
		return max(a, max(b, c, d));
	}
	
};

#endif

