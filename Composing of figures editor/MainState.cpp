#include "MainState.h"
#include "Button.h"
#include "ResourceHolder.h"
#include "Figure.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

const int MainState::workspace_border = 120;

MainState::MainState(StateStack& stack, Context context)
	:State(stack, context)
	,GUI_container(context)
	,scene_graph()
{
	sf::Texture& texture = context.textures->get(Textures::FirstPage);
	background_sprite.setTexture(texture);

	auto playButton = std::make_shared<GUI::Button>(context);
	playButton->setPosition(50, 35);
	playButton->setText("Triangle");
	playButton->setCallback([this] ()
	{
		std::unique_ptr<Figure> background(new Figure(Figure::Type::Triangle));
		background->setPosition(300, 300);
		scene_graph.attachChild(std::move(background));
	});

	auto settingsButton = std::make_shared<GUI::Button>(context);
	settingsButton->setPosition(150, 35);
	settingsButton->setText("Rectangle");
	settingsButton->setCallback([this] ()
	{
		std::unique_ptr<Figure> sprite(new Figure(Figure::Type::Rectangle));
		sprite->setPosition(300, 300);
		scene_graph.attachChild(std::move(sprite));
	});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(250, 35);
	exitButton->setText("Circle");
	exitButton->setCallback([this] ()
	{
		std::unique_ptr<Figure> sprite(new Figure(Figure::Type::Ellipsó));
		sprite->setPosition(300, 300);
		scene_graph.attachChild(std::move(sprite));
	});

	GUI_container.pack(playButton);
	GUI_container.pack(settingsButton);
	GUI_container.pack(exitButton);
}

void MainState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(background_sprite);
	window.draw(scene_graph);
	window.draw(GUI_container);
}

bool MainState::update(sf::Time dt)
{
	//scene_graph.update(dt)
	return true;
}

bool MainState::handleEvent(const sf::Event& event)
{
	GUI_container.handleEvent(event);
	if (event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*context.window));
		if (mouse_position.y > workspace_border)
			scene_graph.checkNodeCollision(mouse_position);
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Delete)
	{
		scene_graph.removeFigure();
	}
	return false;
}