#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "GraphicWindow.h"
#include "globals.h"

class Player
{
private:

	// Characteristics relative to the person
	std::string m_name;
	unsigned int m_height;
	unsigned int m_weight;
	unsigned int m_age;

	// Characteristics relative to rugby skill
	unsigned int m_movement;
	unsigned int m_action;
	unsigned int m_force;
	unsigned int m_defence;
	unsigned int m_dexterity;
	unsigned int m_kicking;

	// Characteristics relative to ongoing game
	unsigned int m_number;
	unsigned int m_team;
	sf::Vector2u m_position;
	bool m_isSelected;
	bool m_hasBall;
	PlayerState m_state;

	// Characteristics for display purposes
	sf::Sprite m_sprite;
	sf::Font m_font;
	sf::Text m_jersey;

public:

	Player() {}

	Player(	const std::string & name, unsigned int height, unsigned int weight, unsigned int age,
			unsigned int speed, unsigned int action,
			unsigned int force, unsigned int defence, unsigned int dexterity, unsigned int kicking,
			unsigned int number, unsigned int team, sf::Vector2u position, sf::Texture & texture)
		:m_name(name), m_height(height), m_weight(weight), m_age(age),
		 m_movement(speed), m_action(action),
		 m_force(force), m_defence(defence), m_dexterity(dexterity), m_kicking(kicking),
		 m_number(number), m_team(team), m_position(position),
		 m_isSelected(false), m_hasBall(false), m_state(PlayerState::NONE),
		 m_sprite(texture) {

		if (!m_font.loadFromFile("assets/arial.ttf")) {
			std::cout << "Player - Couldn't load front from file" << std::endl;
		}

		m_sprite.setPosition(gridToScreen(m_position));

		sf::Vector2f padding(7.f, 8.f);
		if (m_number < 10)
			padding = sf::Vector2f(12.f, 8.f);
		m_jersey.setPosition(gridToScreen(m_position) + padding);

		m_jersey.setCharacterSize(14);
		m_jersey.setColor(sf::Color::White);
		m_jersey.setStyle(sf::Text::Bold);
		m_jersey.setString(std::to_string(m_number));
	}

	~Player() {}

	void select(bool b = true) {
		m_isSelected = b;

		if (b) {
			m_jersey.setColor(sf::Color::Green);
		}
		else {
			m_jersey.setColor(sf::Color::White);
		}
	}

	sf::Vector2u getPosition() {
		return m_position;
	}

	void draw(GraphicWindow & window) {
		window.draw(m_sprite);
		m_jersey.setFont(m_font);
		window.draw(m_jersey);
	}
};

