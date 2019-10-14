#pragma once
#include <SFML/Graphics.hpp>
// class to store thin lines which will be use to calculate intersect
// between other objects.
class visionLine : sf::RectangleShape
{
	// rectangle for visual representation 
	sf::RectangleShape* shape;
	
	// position of the base of the vector
	sf::Vector2f* pos;

	// current angle of the line , 0' is upwards, measured in degrees
	unsigned int distance = INT_MAX;
	bool isDetecting = false;
	float angle;
public:
	// constructor
	visionLine(sf::RectangleShape& line, sf::Vector2f& base, float ang);
	// accessors for private values
	void setAngle(float newAng) { angle = newAng; };
	float getAngle() { return this->angle; };
	void setPos(sf::Vector2f& newPos) { pos = &newPos; };
	sf::Vector2f* getPos() { return this->pos; };
	sf::RectangleShape* getShape() { return this->shape; };

	void setDistance(int newDis) { this->distance = newDis; };
	bool getDetecting() { return isDetecting; };
	void setDetecting(bool newStatus) { this->isDetecting = newStatus; };
	int getDistance() { return this->distance; };
	// destructor
	~visionLine();
};

