#include "visionLine.h"


// constructor
visionLine::visionLine(sf::RectangleShape& l, sf::Vector2f& base, float ang)
{
	this->shape = &l;
	this->pos = &base;
	this->angle = ang;
}

// destructor
visionLine::~visionLine()
{
	this->shape = NULL;
	this->pos = NULL;
}
