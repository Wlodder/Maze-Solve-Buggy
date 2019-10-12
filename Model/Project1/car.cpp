#include "car.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

// set velocity of car
void car::setVelocity(sf::Vector2f &veloVec)
{
	this->velocity = &veloVec;
}

// set body of car
void car::setBody(sf::RectangleShape &body)
{
	this->body = &body;
}

// destructor
car::~car()
{
	velocity = NULL;
	body = NULL;
}

// rotate the velocity vector of the car
void car::rotVelocity(float angle)
{
	auto convertRads = [angle](bool isCos) {return (isCos ? cos(angle * M_PI / 180) : sin(angle * M_PI / 180)); };

	// convert angle to radians and perform function on it
	float cosTheta = convertRads(true);
	float sinTheta = convertRads(false);

	// temporary variables to capture velocity of 
	float xtemp = velocity->x;
	float ytemp = velocity->y;

	// update the velocity of the new vector using rotational matrix formula
	velocity->x = xtemp * cosTheta - ytemp * sinTheta;
	velocity->y = xtemp * sinTheta + ytemp * cosTheta;

	// for debug
	//std::cout << "x : " <<velocity->x  << " y : " << velocity->y << " | ";
}

// rotate the body of the car using the angle and built in method of the 
// sf::RectangleShape->setRotation
void car::rotateBody(float angle)
{
	body->setRotation(body->getRotation() + angle);
	
	// for debug
	//std::cout << "angle : " << body->getRotation() << std::endl;
}

// rotate the vision lines of the car similar to rotating the car itself
void car::rotateLines(float angle)
{
	for (auto& line : this->lines)
	{
		line->getShape()->setRotation(line->getShape()->getRotation() + angle);
	}
}

// move the lines of the car similar to moving the car itself
void car::moveLines(bool forwards)
{
	for (auto& lin : this->lines)
	{
		lin->getShape()->setPosition(lin->getShape()->getPosition() + *velocity * (forwards ? 1.f : -1.f));
	}
}

// move the car in the direction of the velocity
void car::move(bool forwards)
{
	body->setPosition(body->getPosition() + *velocity * (forwards ? 1.f : -1.f));
	this->moveLines(forwards);
}

void car::setSpeed(sf::Vector2f& newSpeed)
{
	this->speed = sqrt(newSpeed.x * newSpeed.x + newSpeed.y * newSpeed.y);
}


