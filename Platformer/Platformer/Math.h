#ifndef MATH
#define MATH

#include "SFML/Graphics.hpp"
#include <iostream>


using namespace sf;


inline float VectorDot(Vector2f v1, Vector2f v2) { return  v1.x * v2.x + v1.y * v2.y; }
inline Vector2f Normalized(Vector2f vector)
{
	Vector2f result = vector;
	double magnitude = std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
	if (magnitude != 0)
	{
		result = Vector2f(vector.x / magnitude, vector.y / magnitude);
	}
	return result;
}

inline float ConvertNumberRange(float OldValue, float OldMin, float OldMax,float NewMin, float NewMax)
{	
	return ((OldValue - OldMin) / (OldMax - OldMin)) * (NewMax - NewMin) + NewMin;
}

#endif // !MATH
