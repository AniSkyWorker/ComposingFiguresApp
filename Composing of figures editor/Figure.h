#pragma once

#include "Command.h"
#include "SceneNode.h"
#include "FrameNode.h"

struct Figure : public SceneNode
{
	enum Type
	{
		Rectangle,
		Triangle,
		Ellipsó,
		TypeCount
	};

	Figure(Type type);

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateCurrent(sf::Time dt) override;
	//virtual unsigned int getCategory() const override;
	virtual sf::FloatRect getBoundingRect() const override;

	virtual bool isMarkedForRemoval() const override;

	Type type;
	sf::CircleShape figure;
	bool hasFrame;
};