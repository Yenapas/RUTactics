#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	Game * game = Game::get();

	game->init();

	while (!game->isTerminated()) {
		game->updateWorld();
		game->render();
	}

	/*sf::RenderWindow window(sf::VideoMode(1856, 866), "Super Rugby !!!");


	sf::Texture red_tile;
	if (!red_tile.loadFromFile("assets/red_tile.png")) {

	}
	sf::Texture blue_tile;
	if (!blue_tile.loadFromFile("assets/blue_tile.png")) {

	}
	sf::Texture pattern;
	if (!pattern.loadFromFile("assets/field.png")) {

	}

	sf::Sprite red_sprite(red_tile);
	red_sprite.setPosition(gridToScreen(sf::Vector2u(0,0)));
	sf::Sprite blue_sprite(blue_tile);
	blue_sprite.setPosition(gridToScreen(sf::Vector2u(2,3)));
	sf::Sprite tile_pattern(pattern);
	tile_pattern.setPosition(0, 0);



	sf::RectangleShape shape(sf::Vector2f(1856, 866));
	shape.setPosition(0, 0);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.draw(tile_pattern);
		window.draw(red_sprite);
		window.draw(blue_sprite);
		window.display();
	}*/

	return 0;
}