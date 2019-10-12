#include "Utils.h"
#include <math.h>
/*
float Utils::findDistance(line* a, line* b)
{
	float a1 = a->getEndPoint()->y - a->getStartPoint()->y;
	float b1 = a->getStartPoint()->x - a->getEndPoint()->x;
	float c1 = a1 * (a->getStartPoint()->x) + b1 * (a->getStartPoint()->y);

	float a2 = b->getEndPoint()->y - b->getStartPoint()->y;
	float b2 = b->getStartPoint()->x - b->getEndPoint()->x;
	float c2 = a2 * (b->getStartPoint()->x) + b2 * (b->getStartPoint()->y);
	
	float determinant = a1 * b2 - a2 * b1;

	if (!determinant)
		return -1;
	else
	{
		float x = (b2*c1 - b1 * c2) / determinant;
		float y = (a1*c2 - a2 * c1) / determinant;
		float dif1 = x - a->getStartPoint()->x;
		float dif2 = y - a->getStartPoint()->y;
		return sqrt(dif1*dif1 + dif2 * dif2);
	}
}*/

