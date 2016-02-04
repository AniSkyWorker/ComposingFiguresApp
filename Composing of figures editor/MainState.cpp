#include "MainState.h"
#include "Button.h"
#include "ResourceHolder.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include "Command.h"

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
	,figure_frame(nullptr)
	,is_resize(false)
{
	sf::Texture& texture = context.textures->get(Textures::FirstPage);
	background_sprite.setTexture(texture);

	initButtons();
}

void MainState::createFigure(Figure::Type type)
{
	std::unique_ptr<Figure> figure(new Figure(type));
	figure->setPosition(300, 300);
	scene_graph.attachChild(std::move(figure));
}

void MainState::initButtons()
{
	auto TriangleButton = std::make_shared<GUI::Button>(context);
	TriangleButton->setPosition(50, 35);
	TriangleButton->setText("Triangle");
	TriangleButton->setCallback([this]()
	{
		createFigure(Figure::Type::Triangle);
	});

	auto RectangleButton = std::make_shared<GUI::Button>(context);
	RectangleButton->setPosition(150, 35);
	RectangleButton->setText("Rectangle");
	RectangleButton->setCallback([this]()
	{
		createFigure(Figure::Type::Rectangle);
	});

	auto CircleButton = std::make_shared<GUI::Button>(context);
	CircleButton->setPosition(250, 35);
	CircleButton->setText("Circle");
	CircleButton->setCallback([this]()
	{
		createFigure(Figure::Type::Ellipsó);
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
	scene_graph.update(dt);

	if (is_pressed && selected_figure)
	{
		if (is_resize)
		{
			if (selected_figure->figure.getRadius() > 20.f || sf::Vector2f(sf::Mouse::getPosition(*context.window)).x - mouse_position.x > 0)
			{
				float size_range = (sf::Vector2f(sf::Mouse::getPosition(*context.window)).x - mouse_position.x) / 10.f;
				figure_frame->frame_shape.setSize(sf::Vector2f(figure_frame->getBoundingRect().width + size_range, figure_frame->getBoundingRect().width + size_range));
				selected_figure->figure.setRadius(figure_frame->frame_shape.getSize().x / 2.f);
			}
		}

		selected_figure->setPosition(mouse_position - delta);
		if(selected_figure->getBoundingRect().top < workspace_border)
			selected_figure->setPosition(mouse_position.x - delta.x, workspace_border + selected_figure->getBoundingRect().height / 2.f);
	}
	return true;
}

bool MainState::handleEvent(const sf::Event& event)
{
	GUI_container.handleEvent(event);

	if(!is_resize || (is_resize && mouse_position == sf::Vector2f()))
		mouse_position = sf::Vector2f(sf::Mouse::getPosition(*context.window));
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		if (mouse_position.y > workspace_border)
		{
			if (scene_graph.checkNodeCollision(mouse_position))
			{
				is_pressed = true;

				selected_figure = static_cast<Figure*>(scene_graph.getSelectedFigure());
				figure_position = selected_figure->getPosition();
				delta = mouse_position - figure_position;

				if (!selected_figure->hasFrame)
				{
					std::unique_ptr<FrameNode> frame(new FrameNode(selected_figure->getBoundingRect()));
					figure_frame = frame.get();
					selected_figure->attachChild(std::move(frame));
					selected_figure->hasFrame = true;
				}
			}
			else
			{
				selected_figure = nullptr;
				figure_frame = nullptr;
			}

			if (selected_figure)
			{
				if(figure_frame->checkNodeCollision(mouse_position))
					is_resize = true;
			}
		}
	}
	if (event.type == sf::Event::MouseButtonReleased)
	{
		is_pressed = false;
		is_resize = false;
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Delete)
	{
		scene_graph.removeFigure();
	}
	return true;
}