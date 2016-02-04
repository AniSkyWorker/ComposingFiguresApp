#include "FrameNode.h"
#include <iostream>


FrameNode::FrameNode(sf::FloatRect object_bounds)
	:bounding_rect(object_bounds)
	,frame_shape()
	,size_points()
{

	selected = true;
	frame_shape.setSize(sf::Vector2f(object_bounds.width, object_bounds.height));
	frame_shape.setFillColor(sf::Color::Transparent);
	frame_shape.setOutlineColor(sf::Color::Green);
	frame_shape.setOrigin(object_bounds.width / 2.f, object_bounds.height / 2.f);
	frame_shape.setOutlineThickness(1.f);

	size_points[0].setFillColor(sf::Color::Black);
	size_points[0].setRadius(8.f);
	size_points[0].setOrigin(size_points[0].getGlobalBounds().width / 2.f, size_points[0].getGlobalBounds().height / 2.f);

	size_points[1].setFillColor(sf::Color::Black);
	size_points[1].setRadius(8.f);
	size_points[1].setOrigin(size_points[0].getGlobalBounds().width / 2.f, size_points[0].getGlobalBounds().height / 2.f);

	size_points[2].setFillColor(sf::Color::Black);
	size_points[2].setRadius(8.f);
	size_points[2].setOrigin(size_points[0].getGlobalBounds().width / 2.f, size_points[0].getGlobalBounds().height / 2.f);
	
	size_points[3].setFillColor(sf::Color::Black);
	size_points[3].setRadius(8.f);
	size_points[3].setOrigin(size_points[0].getGlobalBounds().width / 2.f, size_points[0].getGlobalBounds().height / 2.f);

	updatePoints();
	
}
void FrameNode::updatePoints()
{
	size_points[0].setPosition(frame_shape.getGlobalBounds().left + 5, frame_shape.getGlobalBounds().top + 5);
	size_points[1].setPosition(frame_shape.getGlobalBounds().left + frame_shape.getGlobalBounds().width - 5, frame_shape.getGlobalBounds().top + 5);
	size_points[2].setPosition(frame_shape.getGlobalBounds().left + frame_shape.getGlobalBounds().width - 5, frame_shape.getGlobalBounds().top + frame_shape.getGlobalBounds().height - 5);
	size_points[3].setPosition(frame_shape.getGlobalBounds().left + 5, frame_shape.getGlobalBounds().top + frame_shape.getGlobalBounds().height - 5);
}
void FrameNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(frame_shape, states);
	target.draw(size_points[0], states);
	target.draw(size_points[1], states);
	target.draw(size_points[2], states);
	target.draw(size_points[3], states);
}

void FrameNode::updateCurrent(sf::Time dt)
{
	frame_shape.setOrigin(frame_shape.getGlobalBounds().width / 2.f, frame_shape.getGlobalBounds().height / 2.f);

	updatePoints();
}

sf::FloatRect FrameNode::getBoundingRect() const
{
	return getWorldTransform().transformRect(frame_shape.getGlobalBounds());
}

bool FrameNode::checkNodeCollision(sf::Vector2f position)
{
	for (size_t i = 0; i < 4; i++)
		if (getWorldTransform().transformRect(size_points[i].getGlobalBounds()).contains(position))
			return true;
	return false;
}