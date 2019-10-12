#pragma once
#include "collisionObj.h"
#include "visionLine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "car.h"

namespace Utils {
	//static float collided = 0;
	static int relativeDistance = 0;
	static bool willCollide = false;


	static float calculateLength(float a, float b)
	{
		return sqrt(a * a + b * b);
	}

	static void checkCollision(collisionObj& obj, visionLine& v, car& c)
	{
		willCollide = obj.getGlobalBounds().intersects(v.getShape()->getGlobalBounds());
		
		/*if (willCollide)
		{
			if (collided)
			{
				collided -= c.getSpeed();
			}
			else
				collided = calculateLength(v.getShape()->getGlobalBounds().height, v.getShape()->getGlobalBounds().width);
		}
		else
			collided = 0;
		std::cout << collided << std::endl;*/
	};

	static void findRelativeDistance(const collisionObj& obj, car& c)
	{
		if (!willCollide)
		{	
			relativeDistance = 0;
			return;
		}
		float carXPos = c.getBody()->getPosition().x;
		float carYPos = c.getBody()->getPosition().y;
		float objXPos = obj.getPosition().x;
		float objYPos = obj.getPosition().y;
	
		relativeDistance = calculateLength(carXPos - objXPos, carYPos - objYPos) - c.getBody()->getLocalBounds().height/2;
		std::cout << relativeDistance << std::endl;
	}
}