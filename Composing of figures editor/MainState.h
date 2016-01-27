#pragma once

#include "State.h"
#include "Container.h"
#include "SceneNode.h"
#include "Figure.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

struct MainState : public State
{
	MainState(StateStack& stack, Context context);

		virtual void draw() override;
		virtual bool update(sf::Time dt) override;
		virtual bool handleEvent(const sf::Event& event);

		sf::Sprite background_sprite;
		GUI::Container GUI_container;
		SceneNode scene_graph;

		static const int workspace_border;

		//������� � �������� handler ��� sceneNode
		bool is_pressed;
		Figure* selected_figure;
		sf::Vector2f figure_position;
		sf::Vector2f mouse_position;
		sf::Vector2f delta;
};

