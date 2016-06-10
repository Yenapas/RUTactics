#pragma once

#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "EventManager.h"

class GraphicWindow
{
private:

	sf::RenderWindow m_sfWindow;
	sf::Vector2u m_size;
	std::string m_title;
	bool m_terminated;

	EventManager m_eventManager;
	bool m_focused;

	void open() {
		auto style = (sf::Style::Titlebar | sf::Style::Close);
		m_sfWindow.create(sf::VideoMode(m_size.x, m_size.y), m_title, style);
		m_sfWindow.setFramerateLimit(60);
	}

	void close() {
		m_sfWindow.close();
	}

public:

	GraphicWindow(const std::string & title, const sf::Vector2u & size)
		:m_size(size), m_title(title), m_terminated(false) {
		open();
	}

	~GraphicWindow() {
		close();
	}

	void setupEvents();

	void handleEvents();

	void clear() {
		m_sfWindow.clear(sf::Color::Black);
	}

	void render() {
		m_sfWindow.display();
	}

	void draw(sf::Drawable & object) {
		m_sfWindow.draw(object);
	}

	bool isTerminated() const {
		return m_terminated;
	}

	sf::Vector2u getSize() const {
		return m_size;
	}

	bool isFocused() {
		return m_focused;
	}

	EventManager * getEventManager() {
		return &m_eventManager;
	}

	void closeEvent(EventDetails * details = nullptr);
};

