#pragma once

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID
	{
		TitleScreen,

		FirstPage,

		ButtonNormal,
		ButtonPressed,
		ButtonSelected
	};
}

namespace Fonts 
{
	enum ID
	{
		Main,
	};
}

template <typename Resource, typename Identifier> struct ResourceHolder;
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;