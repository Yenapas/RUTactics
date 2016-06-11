#pragma once

#include <string>
#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include "GraphicWindow.h"

class ClickButton
{
private:

	sf::IntRect m_rectangle;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::RectangleShape m_background;
	sf::Font m_font;
	unsigned int m_fontSize;
	sf::Text m_label;

	std::function<void(void)> m_callback;

public:
	ClickButton(sf::Vector2i pos, sf::Vector2i size, std::string label)
	:m_rectangle(pos, size), m_position(pos), m_size(size), m_background(m_size), m_font(), m_fontSize(14), m_label(label, m_font) {

		if (!m_font.loadFromFile("assets/arial.ttf")) {
			std::cout << "ClickButton - Couldn't load font from file" << std::endl;
		}
		m_label.setFont(m_font);
		m_label.setCharacterSize(m_fontSize);
		m_label.setColor(sf::Color::White);
		m_label.setStyle(sf::Text::Bold);
		float textWidth = (m_fontSize * 0.66f) * m_label.getString().getSize();
		sf::Vector2f offset((m_size.x - textWidth) / 2, (m_size.y - m_fontSize) / 2);
		m_label.setPosition(m_position + offset);
		m_background.setPosition(m_position);
		m_background.setOutlineColor(sf::Color::Black);
		m_background.setOutlineThickness(2.f);
		m_background.setFillColor(sf::Color(100, 100, 100, 255));
	}

	~ClickButton() {}

	template <class T>
	void addCallback(void(T::*func)(void), T * instance) {
		auto temp = std::bind(func, instance);
		m_callback = temp;
	}

	void handleClick(sf::Vector2i pos) {
		if (m_rectangle.contains(pos))
			m_callback();
	}

	void draw(GraphicWindow & window) {
		window.draw(m_background);
		m_label.setFont(m_font);
		window.draw(m_label);
	}
};

