#pragma once

#include "SceneNode.h"

struct FrameNode : public SceneNode
{
	FrameNode(sf::FloatRect object_bounds);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateCurrent(sf::Time dt) override;
	virtual sf::FloatRect getBoundingRect() const override;
	virtual bool checkNodeCollision(sf::Vector2f position) override;

	void updatePoints();

	sf::FloatRect bounding_rect;

	sf::RectangleShape frame_shape;
	sf::CircleShape size_points[4];
};

