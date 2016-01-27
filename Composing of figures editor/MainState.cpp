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
	,is_pressed(false)
	,selected_figure(nullptr)
	,figure_position()
	,mouse_position()
	,delta()
{
	sf::Texture& texture = context.textures->get(Textures::FirstPage);
	background_sprite.setTexture(texture);

	auto TriangleButton = std::make_shared<GUI::Button>(context);
	TriangleButton->setPosition(50, 35);
	TriangleButton->setText("Triangle");
	TriangleButton->setCallback([this] ()
	{
		std::unique_ptr<Figure> triangle(new Figure(Figure::Type::Triangle));
		triangle->setPosition(300, 300);
		scene_graph.attachChild(std::move(triangle));
	});

	auto RectangleButton = std::make_shared<GUI::Button>(context);
	RectangleButton->setPosition(150, 35);
	RectangleButton->setText("Rectangle");
	RectangleButton->setCallback([this] ()
	{
		std::unique_ptr<Figure> rectangle(new Figure(Figure::Type::Rectangle));
		rectangle->setPosition(300, 300);
		scene_graph.attachChild(std::move(rectangle));
	});

	auto CircleButton = std::make_shared<GUI::Button>(context);
	CircleButton->setPosition(250, 35);
	CircleButton->setText("Circle");
	CircleButton->setCallback([this] ()
	{
		std::unique_ptr<Figure> ellipsy(new Figure(Figure::Type::Ellipsó));
		ellipsy->setPosition(300, 300);
		scene_graph.attachChild(std::move(ellipsy));
	});

	GUI_container.pack(TriangleButton);
	GUI_container.pack(RectangleButton);
	GUI_container.pack(CircleButton);
}

void MainState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
 	window.draw(scene_graph);
	window.draw(background_sprite);
	window.draw(GUI_container);
}

bool MainState::update(sf::Time dt)
{
	if (is_pressed && selected_figure != nullptr)
	{
		selected_figure->setPosition(mouse_position - delta);
		if(selected_figure->getBoundingRect().top < workspace_border)
			selected_figure->setPosition(mouse_position.x - delta.x, workspace_border + selected_figure->getBoundingRect().height / 2.f);
	}
	return true;
}

bool MainState::handleEvent(const sf::Event& event)
{
	GUI_container.handleEvent(event);
	mouse_position = sf::Vector2f(sf::Mouse::getPosition(*context.window));
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		if (mouse_position.y > workspace_border)
			if (scene_graph.checkNodeCollision(mouse_position))
			{
				is_pressed = true;
				selected_figure = static_cast<Figure*>(scene_graph.getSelectedFigure());
				figure_position = selected_figure->getPosition();
				delta = mouse_position - figure_position;
			}
	}
	if (event.type == sf::Event::MouseButtonReleased)
		is_pressed = false;
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Delete)
	{
		scene_graph.removeFigure();
	}
	return true;
}