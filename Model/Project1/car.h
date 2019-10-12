#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "visionLine.h"
#include "collisionObj.h"

class car 
{
	// vector of vision lines for getting observations from environment
	std::vector<visionLine*> lines;

	// velocity of car
	sf::Vector2f* velocity;

	// representation of the body of the car
	sf::RectangleShape* body;
	
	// integer to determine whether body is rotating constantly
	// negative for one direction , pos for other
	int rotating = 0;
	float speed;
	// angle used if rotating != 0
	float rotationalAngle = 0;


public:
	// rotate the velocity vector
	void rotVelocity(float angle);

	// constructor
	car(sf::Vector2f* veloVec, sf::RectangleShape* bodyA) { velocity = veloVec; body = bodyA; setSpeed(*veloVec); };
	// accessor methods
	void setVelocity(sf::Vector2f &veloVec);
	float getRotationalAngle() { return this->rotationalAngle; };
	void setRotationalAngle(float newAngle) { this->rotationalAngle = newAngle; };
	void setBody(sf::RectangleShape &body);
	sf::RectangleShape* getBody() { return body; };
	std::vector<visionLine*>& getLines() { return this->lines; };
	sf::Vector2f* getVelocity() { return this->velocity; };
	void setSpeed(sf::Vector2f& newSpeed);
	float getSpeed() { return this->speed; };
	
	// methods for manipulating the vision lines 

	// add vision line to the vector of vision lines
	void addLine(visionLine& line) { this->lines.push_back(&line); };

	void moveLines(bool forwards);
	void rotateLines(float angle);
	
	// methods for manipulating car body attributes
	void changeSpeed(float speedFactor) { *velocity += (*velocity * speedFactor);};
	void rotateBody(float angle);
	void move(bool forwards);
	void rotate(float angle) { this->rotVelocity(angle); this->rotateBody(angle); this->rotateLines(angle); };
	
	~car();
};
