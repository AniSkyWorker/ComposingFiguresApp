#include "SceneNode.h"
#include <algorithm>
#include <cassert>
#include "Command.h"

SceneNode::SceneNode(Category::Type category)
	:children()
	,parent(nullptr)
	,default_category(category)
	,selected(false)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(children.begin(), children.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != children.end());

	Ptr result = std::move(*found);
	result->parent = nullptr;
	children.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (Ptr& child : children)
		child->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);

	if(isSelected())
		drawBoundingRect(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& child : children)
		child->draw(target, states);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::callCommand(const Command& command, sf::Time dt)
{
	if (command.category & getCategory())
		command.action(*this, dt);
	for (const Ptr& child : children)
		child->callCommand(command, dt);
}

unsigned int SceneNode::getCategory() const
{
	return default_category;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

bool SceneNode::checkNodeCollision(sf::Vector2f position)
{
	for (int i = children.size() -1; i >= 0; i--)
	{
		if (children[i]->getBoundingRect().contains(position))
		{
			children[i]->selected = true;
			for (int j = children.size() - 1; j >= 0; j--)
				if (j != i)
					children[j]->selected = false;
			return true;
		}
		else
		{
			children[i]->selected = false;
		}
	}
	return false;
}

void SceneNode::removeFigure()
{
	auto deleteFigureBegin = std::remove_if(children.begin(), children.end(), std::mem_fn(&SceneNode::isSelected));
	children.erase(deleteFigureBegin, children.end());

//	std::for_each(children.begin(), children.end(), std::mem_fn(&SceneNode::removeFigure));
}

bool SceneNode::isMarkedForRemoval() const
{
	return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
	return false;
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

bool SceneNode::isSelected() const
{
	return selected;
}

SceneNode* SceneNode::getSelectedFigure()
{
	for (const Ptr& child : children)
		if (child->isSelected())
			return child.get();

	std::for_each(children.begin(), children.end(), std::mem_fn(&SceneNode::getSelectedFigure));
}