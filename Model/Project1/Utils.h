#pragma once
#include "collisionObj.h"
#include "visionLine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "car.h"
#include <vector>

namespace Utils {
	
	static std::vector<visionLine*> vLines;
	static std::vector<collisionObj*> objects;

	static int findDistanceReturn(const collisionObj& obj, car& c, visionLine& v);

	static void addvLine(visionLine& line)
	{
		vLines.push_back(&line);
	}

	static void addObject(collisionObj& obj)
	{
		objects.push_back(&obj);
	}

	static float calculateLength(float a, float b)
	{
		return sqrt(a * a + b * b);
	}

	static bool checkCollision(collisionObj& obj, visionLine& v)
	{
		return obj.getGlobalBounds().intersects(v.getShape()->getGlobalBounds());
	};

	static void findAllDistances(car& c)
	{
		for (auto& v : Utils::vLines)
		{
			int minimumDistance = INT_MAX;
			for (auto& o : Utils::objects)
			{
				int curr = findDistanceReturn(*o, c, *v);
				minimumDistance = (curr < minimumDistance) ? curr : minimumDistance;
			}
			v->setDistance(minimumDistance);
		}
	}

	static void findAllCollisions()
	{
		for (auto& v : Utils::vLines)
		{
			bool isDetecting = false;  
			for (auto& o : Utils::objects)
			{
				isDetecting |= checkCollision(*o, *v);
			}
			v->setDetecting(isDetecting);
		}
	}

	static void findRelativeDistance(const collisionObj& obj, car& c, visionLine& v)
	{
		// need to make distance take into account the angle at which the vision line is at
		if (!v.getDetecting())
		{	
			v.setDistance(0);
			return;
		}
		
			float carXPos = c.getBody()->getPosition().x;
			float carYPos = c.getBody()->getPosition().y;
			float objXPos = obj.getPosition().x;
			float objYPos = obj.getPosition().y;

			v.setDistance(calculateLength(carXPos - objXPos, carYPos - objYPos) - c.getBody()->getLocalBounds().height / 2
							- (obj.getLocalBounds().width + obj.getLocalBounds().height) / 2);
	}

	static void printDistances()
	{
		std::cout << "distances : ";
		for (std::vector<visionLine*>::iterator itr = vLines.begin(); itr != vLines.end(); itr++)
		{
			std::cout << (*itr)->getDistance() << ", " ;
		}
		std::cout << std::endl;
	}

	static int findDistanceReturn(const collisionObj& obj, car& c, visionLine& v)
	{
		// need to make distance take into account the angle at which the vision line is at
		if (!v.getDetecting())
		{
			v.setDistance(0);
			return INT_MAX;
		}

		float carXPos = c.getBody()->getPosition().x;
		float carYPos = c.getBody()->getPosition().y;
		float objXPos = obj.getPosition().x;
		float objYPos = obj.getPosition().y;

		return abs(calculateLength(carXPos - objXPos, carYPos - objYPos) - c.getBody()->getLocalBounds().height / 2
			- (obj.getLocalBounds().width + obj.getLocalBounds().height) / 2);
	}
}