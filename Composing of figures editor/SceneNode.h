#pragma once

#include <vector>
#include <memory>
#include <set>
#include <SFML/Graphics.hpp>
#include "ObjectCategory.h"

struct Command;
struct CommandQueue;

struct SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

	SceneNode(Category::Type category = Category::None);

	void attachChild(Ptr&& child);
	Ptr	detachChild(const SceneNode& node);

	void update(sf::Time dt);

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

	void callCommand(const Command& command, sf::Time dt);
	virtual unsigned int getCategory() const;

	virtual bool checkNodeCollision(sf::Vector2f position);
	void removeFigure();
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool isMarkedForRemoval() const;
	virtual bool isDestroyed() const;

	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isSelected() const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;
	SceneNode* getSelectedFigure();

	std::vector<Ptr> children;
	SceneNode* parent;
	Category::Type default_category;
	bool selected;
};

bool collision(const SceneNode& lhs, const SceneNode& rhs);