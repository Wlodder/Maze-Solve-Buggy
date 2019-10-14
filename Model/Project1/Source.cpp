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

	// collision objects
	sf::RectangleShape col(sf::Vector2f(100,250));
	col.setFillColor(sf::Color::Magenta);
	col.setPosition(20, 300);
	collisionObj block(col);

	sf::RectangleShape col2(sf::Vector2f(200, 25));
	col2.setFillColor(sf::Color::Yellow);
	col2.setPosition(100, 100);
	collisionObj block2(col2);

	sf::RectangleShape line(sf::Vector2f (1.f, 250.f));
	sf::RectangleShape linePerpendicular(sf::Vector2f(1.f, 250.f));
	sf::Vector2f lineBase = rect.getOrigin();
	sf::Vector2f testVec(10, 10);
	sf::Vector2f testVecPerpen(10, 10);
	::visionLine visionLine(line, testVec, 0);
	::visionLine visionLinePerpen(linePerpendicular, testVecPerpen, 0);
	sf::Vector2f center(windowHeight/2, windowWidth/2);
	linePerpendicular.setPosition(center);
	linePerpendicular.setRotation(270);
	line.setPosition(center);
	rect.setPosition(center);
	rect.setOrigin(rectSize / 2.f);
	line.setRotation(180);
	sf::RectangleShape* myBody = &rect;
	sf::Vector2f* velo = &velocityVector;
	car myCar(velo, myBody);
	block.setPosition(100, 200);
	myCar.addLine(visionLine);
	myCar.addLine(visionLinePerpen);
	rect.setFillColor(sf::Color::Blue);
	Utils::addvLine(visionLine);
	Utils::addvLine(visionLinePerpen);
	Utils::addObject(block);
	Utils::addObject(block2);
	// collision thread
	// std::thread collisionDetectThread(&Utils::checkCollision,std::ref(block),std::ref(visionLine));

	// main loop
	while (window.isOpen())
	{
		// 1 : 2 thread calcs to distance
		/*
		std::thread collisionDetectThreadForward(&Utils::checkCollision,
			std::ref(block), std::ref(visionLine));
		std::thread collisionDetectThreadPerpen(&Utils::checkCollision,
			std::ref(block), std::ref(visionLinePerpen));
		std::thread distanceDetectThreadForward(&Utils::findRelativeDistance, std::ref(block),
			std::ref(myCar), std::ref(visionLine));
		std::thread distanceDetectThreadPerpen(&Utils::findRelativeDistance, std::ref(block),
			std::ref(myCar), std::ref(visionLinePerpen));*/
		
		std::thread collisionDetectThread(&Utils::findAllCollisions);

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
		window.draw(block2);
		//collisionDetectThreadForward.join();
		//distanceDetectThreadForward.join();
		collisionDetectThread.join();
		//collisionDetectThreadPerpen.join();
		//distanceDetectThreadPerpen.join();
		std::thread distanceThread(&Utils::findAllDistances, std::ref(myCar));
		distanceThread.join();

		Utils::printDistances();

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