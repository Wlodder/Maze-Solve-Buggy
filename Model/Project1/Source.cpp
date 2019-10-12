#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "car.h"
#include "visionLine.h"
#include "collisionObj.h"
#include <random>
#include "Utils.h"
#include <iostream>
#include <thread>

void printGlobal(const sf::RectangleShape& s);

std::default_random_engine generator;
std::normal_distribution<float> distribution(0, 2);
// setting window parameters
const int windowHeight = 800;
const int windowWidth  = 1000;

int main()
{
	// make a window object
	sf::RenderWindow window(sf::VideoMode(windowHeight,windowWidth), "Buggy ENV");
	// making car object and its vision lines 
	sf::Vector2f rectSize(50.f, 100.f);
	sf::Vector2f velocityVector(0.f,0.1f);
	sf::RectangleShape rect(rectSize);
	sf::RectangleShape col(sf::Vector2f(10,50));
	col.setPosition(20, 30);
	sf::RectangleShape line(sf::Vector2f (5.f, 250.f));
	sf::Vector2f lineBase = rect.getOrigin();
	sf::Vector2f testVec(10, 10);
	visionLine visionLine(line, testVec, 0);
	sf::Vector2f center(windowHeight/2, windowWidth/2);
	line.setPosition(center);
	rect.setPosition(center);
	rect.setOrigin(rectSize / 2.f);
	line.setRotation(180);
	sf::RectangleShape* myBody = &rect;
	sf::Vector2f* velo = &velocityVector;
	car myCar(velo, myBody);
	collisionObj block(col);
	block.setPosition(100, 200);
	myCar.addLine(visionLine);
	rect.setFillColor(sf::Color::Blue);

	// collision thread
	//std::thread collisionDetectThread(&Utils::checkCollision,std::ref(block),std::ref(visionLine));

	// main loop
	while (window.isOpen())
	{
		std::thread collisionDetectThread(&Utils::checkCollision,
			std::ref(block), std::ref(visionLine), std::ref(myCar));
		std::thread distanceDetectThread(&Utils::findRelativeDistance, std::ref(block), std::ref(myCar));
		sf::Event event;
		// polling window constantly
		while (window.pollEvent(event))
		{
			
			// check for specific key press combinatiosn 
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed
				& event.key.code == sf::Keyboard::X)
				// close the window
				window.close();
			else if (event.type == sf::Event::KeyPressed & event.key.code == sf::Keyboard::R)
			{
				// reset the buggy
				myCar.getBody()->setPosition(center);
				line.setPosition(center);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				// arrow keys for controlling buggy
				switch (event.key.code)
				{
					
				case sf::Keyboard::Up:
					myCar.changeSpeed(0.1);
					break;
				case sf::Keyboard::Down:
					myCar.changeSpeed(-0.1);
					break;
				
				case sf::Keyboard::Left:
					myCar.setRotationalAngle(myCar.getRotationalAngle() - 0.075f);
					break;
				case sf::Keyboard::Right:
					myCar.setRotationalAngle(myCar.getRotationalAngle() + 0.075f);
					break;
				}
			}
		}
		// rotate car + vision lines
		myCar.rotate(myCar.getRotationalAngle());
		// move car in direction of velocity vector
		myCar.move(false);

		// clear the window to prevent overlapping images
		window.clear();

		// draw car
		window.draw(*(myCar.getBody()));
		window.draw(block);
		collisionDetectThread.join();
		distanceDetectThread.join();

		// draw car's vision lines
		for (int i = 0; i < myCar.getLines().size(); i++)
			window.draw(*((myCar.getLines()[i])->getShape()));

		// display new window
		window.display();
		
	}
	//collisionDetectThread.join();
	return 0;
}

void printGlobal(const sf::RectangleShape& s)
{
	std::cout << "left : " << s.getGlobalBounds().left;
	std::cout << "top : " << s.getGlobalBounds().top;
	std::cout << "right : " << s.getGlobalBounds().width + s.getGlobalBounds().left;
	std::cout << "bottom : " << - s.getGlobalBounds().height + s.getGlobalBounds().top << std::endl;
}