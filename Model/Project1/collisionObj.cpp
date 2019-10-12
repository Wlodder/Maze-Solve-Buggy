#include "collisionObj.h"
#include <SFML/Graphics.hpp>


collisionObj::collisionObj(sf::RectangleShape& shape) : sf::RectangleShape(shape)
{
	this->colShape = &shape.getGlobalBounds();
}


collisionObj::~collisionObj()
{
}
