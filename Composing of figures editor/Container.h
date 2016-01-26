#pragma once

#include "Component.h"
#include "State.h"

#include <vector>
#include <memory>


namespace GUI
{
	struct Container : public Component
	{
			typedef std::shared_ptr<Container> Ptr;
            
			Container(State::Context context);

			void pack(Component::Ptr component);

			virtual bool isSelectable() const override;
			virtual void handleEvent(const sf::Event& event) override;

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			bool hasSelection() const;
			void select(std::size_t index);
			void selectNext();
			void selectPrevious();

			std::vector<Component::Ptr>	children;
			int selected_child;
			sf::RenderWindow& window;
	};
}

