#include "Container.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>


namespace GUI
{
	Container::Container(State::Context context)
		:children()
		,selected_child()
		,window(*context.window)
	{
	}

	void Container::pack(Component::Ptr component)
	{
		children.push_back(component);
	}

	bool Container::isSelectable() const
	{
		return false;
	}

	void Container::handleEvent(const sf::Event& event)
	{
		for (Component::Ptr& child : children)
		{
			if (child->getBoundingRect().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				child->select();
			else
				child->deselect();
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			for (Component::Ptr& child : children)
				if (child->isSelected())
					child->activate();
		}
	}

	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for(const Component::Ptr& child : children)
			target.draw(*child, states);
	}

	bool Container::hasSelection() const
	{
		return selected_child >= 0;
	}

	void Container::select(std::size_t index)
	{
		if (children[index]->isSelectable())
		{
			if (hasSelection())
				children[selected_child]->deselect();

			children[index]->select();
			selected_child = index;
		}
	}

	void Container::selectNext()
	{
		if (!hasSelection())
			return;

		int next = selected_child;
		do
			next = (next + 1) % children.size();
		while (!children[next]->isSelectable());

		select(next);
	}

	void Container::selectPrevious()
	{
		if (!hasSelection())
			return;

		int prev = selected_child;
		do
			prev = (prev + children.size() - 1) % children.size();
		while (!children[prev]->isSelectable());

		select(prev);
	}

}
