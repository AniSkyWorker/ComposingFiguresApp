#include "Application.h"
#include "State.h"
#include "StateIdientificators.h"
#include "TitleState.h"
#include "MainState.h"


const sf::Time Application::time_per_frame = sf::seconds(1.f / 60.f);

Application::Application() 
	:window(sf::VideoMode(1024, 760), "Steel Starling", sf::Style::Close)
	,textures()
	,fonts()
	,statistics_text()
	,statistics_num_frames(0)
	,state_stack(State::Context(window, textures, fonts))
{
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	fonts.load(Fonts::Main, "Media/Sansation.ttf");
	textures.load(Textures::FirstPage, "Media/Textures/1.png");
	textures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.jpg");
	textures.load(Textures::ButtonNormal, "Media/Textures/Button.png");
	textures.load(Textures::ButtonPressed, "Media/Textures/Button.png");
	textures.load(Textures::ButtonSelected, "Media/Textures/Button-selected.png");

	statistics_text.setFont(fonts.get(Fonts::Main));
	statistics_text.setPosition(5.f, 5.f);
	statistics_text.setCharacterSize(10);

	registerStates();
	state_stack.pushState(States::title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	while (window.isOpen())
	{
		sf::Time elapsed_time = clock.restart();
		time_since_last_update += elapsed_time;
		while (time_since_last_update > time_per_frame)
		{
			time_since_last_update -= time_per_frame;
			
			processEvents();
			update(time_per_frame);
			
			if (state_stack.isEmpty())
				window.close();
		}
		updateStatistics(elapsed_time);
		render();
	}
}

void Application::processEvents()
{

	sf::Event event;
	while (window.pollEvent(event))
	{
		state_stack.handleEvent(event);
		switch(event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Application::update(sf::Time dt)
{
	state_stack.update(dt);
}

void Application::render()
{
	window.clear(sf::Color::White);
	state_stack.draw();
	window.setView(window.getDefaultView());
	window.draw(statistics_text);
	window.display();
}
void Application::updateStatistics(sf::Time elapsed_time)
{
	statistics_update_time += elapsed_time;
	statistics_num_frames += 1;

	if (statistics_update_time >= sf::seconds(1.0f))
	{
		statistics_text.setString("FPS = " + std::to_string(statistics_num_frames));

		statistics_update_time -= sf::seconds(1.0f);
		statistics_num_frames = 0;
		
	}
}
void Application::registerStates()
{
	state_stack.registerState<MainState>(States::menu);
	state_stack.registerState<TitleState>(States::title);
}
