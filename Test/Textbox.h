#pragma once

#include <string>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "globals.h"
#include "GraphicWindow.h"

enum class MessageType {
	LOW,
	MEDIUM,
	HIGH,
	DEBUG
};

const sf::Color MSG_COL[] = {	sf::Color::White,	sf::Color::Yellow,	sf::Color::Green,	sf::Color::Red};
const sf::Uint32 MSG_STY[] = {	sf::Text::Regular,	sf::Text::Regular,	sf::Text::Regular,	sf::Text::Bold};

inline sf::Color messageColor(MessageType type) {
	return MSG_COL[int(type)];
}

inline sf::Uint32 messageStyle(MessageType type) {
	return MSG_STY[int(type)];
}

using TextboxMessage = std::pair<MessageType, std::string>;

class Textbox
{
private:

	std::vector<TextboxMessage> m_log;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::RectangleShape m_background;
	sf::Font m_font;
	sf::Text m_text;
	sf::Vector2f m_textOffset;
	unsigned int m_fontSize;
	unsigned int m_lineSpacing;
	unsigned int m_maxLogSize;
	unsigned int m_displaySize;

public:

	Textbox(sf::Vector2f position, sf::Vector2f size, unsigned int maxLogSize, unsigned int fontSize)
		:m_log(maxLogSize), m_position(position), m_size(size), m_background(m_size), m_font(), m_text("", m_font), m_textOffset(5.f, 5.f), m_fontSize(fontSize), m_lineSpacing(3), m_maxLogSize(maxLogSize) {
		
		if (!m_font.loadFromFile("assets/arial.ttf")) {
			std::cout << "Textbox - Couldn't load font from file" << std::endl;
		}
		m_text.setFont(m_font);
		m_text.setCharacterSize(m_fontSize);
		m_text.setColor(sf::Color::White);
		m_text.setPosition(m_position + m_textOffset);
		m_background.setPosition(m_position);
		m_background.setOutlineColor(sf::Color::Black);
		m_background.setOutlineThickness(2.f);
		m_background.setFillColor(sf::Color(85, 85, 85, 200));

		m_displaySize = unsigned int(m_size.y / (fontSize + m_lineSpacing));
		for (unsigned int i = 0; i < m_displaySize; ++i) {
			m_log.push_back(TextboxMessage(MessageType::LOW, ""));
		}
	}

	~Textbox() {}

	void addMessage(const std::string & msg, MessageType type = MessageType::LOW) {
		if (m_log.size() == m_maxLogSize) {
			m_log.erase(m_log.begin(), m_log.begin() + (m_maxLogSize / 2));
		}

		m_log.push_back(TextboxMessage(type, msg));
	}

	void addDebugMessage(const std::string & msg) {
		if (m_log.size() == m_maxLogSize) {
			m_log.erase(m_log.begin(), m_log.begin() + (m_maxLogSize / 2));
		}

		m_log.push_back(TextboxMessage(MessageType::DEBUG, "# "+msg));
	}

	void clear() {
		m_log.clear();
	}

	void draw(GraphicWindow & window) {

		window.draw(m_background);

		for (auto it = m_log.end() - m_displaySize; it < m_log.end(); ++it) {
			m_text.setString(it->second);
			m_text.setColor(messageColor(it->first));
			m_text.setStyle(messageStyle(it->first));
			window.draw(m_text);

			m_text.setPosition(m_text.getPosition() + sf::Vector2f(0.f, m_fontSize + m_lineSpacing));
		}

		m_text.setPosition(m_position + m_textOffset);
	}
};

