#include "Figure.h"
#include "ResourceHolder.h"
#include "CommandQueue.h"
#include "Math.h"
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>


Figure::Figure(Type type)
	:type(type)
{

	switch (type)
	{
	case Triangle:
		figure.setPointCount(3);
		break;
	case Rectangle:
		figure.setPointCount(4);
		break;
	}
	figure.setRadius(80.f);
	figure.setFillColor(sf::Color::Red);
	figure.setOutlineThickness(2.f);
	figure.setOutlineColor(sf::Color::Blue);
	figure.setOrigin(figure.getLocalBounds().width / 2.f, figure.getLocalBounds().height / 2.f);
}

void Figure::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(figure, states);
}

void Figure::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	//
}


sf::FloatRect Figure::getBoundingRect() const
{
	return getTransform().transformRect(figure.getGlobalBounds());
}

bool Figure::isMarkedForRemoval() const
{
	return isDestroyed();
}
