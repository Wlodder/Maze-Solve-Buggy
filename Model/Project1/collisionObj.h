#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Graphics/Rect.hpp>

class collisionObj : public sf::RectangleShape
{
	sf::FloatRect* colShape;
public:
	collisionObj(sf::RectangleShape& shape);
	~collisionObj();

	//sf::FloatRect* getShape() { return this->colShape; };
};

