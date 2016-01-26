#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace GUI
{

	struct Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
		typedef std::shared_ptr<Component> Ptr;

		Component();
		virtual	~Component();

		virtual bool isSelectable() const = 0;
		bool isSelected() const;
		virtual void select();
		virtual void deselect();

		virtual bool isActive() const;
		virtual void activate();
		virtual void deactivate();

		virtual void handleEvent(const sf::Event& event) = 0;

		virtual sf::FloatRect getBoundingRect() const;

		bool is_selected;
		bool is_active;
	};

}
