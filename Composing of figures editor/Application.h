#pragma once
#include <SFML/Graphics.hpp>

#include "StateStack.h"
#include "ResourceIdientificators.h"
#include "ResourceHolder.h"


struct Application
{
	Application();

	void run();
	void processEvents();
	void update(sf::Time time_per_frame);
	void render();

	void updateStatistics(sf::Time elapsed_time);

	void registerStates();

	void loadTextures();

	sf::RenderWindow window;

	sf::Text statistics_text;
	sf::Time statistics_update_time;
	std::size_t	statistics_num_frames;

	static const sf::Time time_per_frame;

	StateStack state_stack;
	TextureHolder textures;
	FontHolder fonts;
};