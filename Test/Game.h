#pragma once

#include <iostream>

#include "Textbox.h"
#include "Team.h"
#include "Ball.h"
#include "globals.h"

#include "GraphicWindow.h"

class Game
{
private:

	static Game * s_instance;
	static const unsigned int NB_TURNS = 30;

	GraphicWindow m_window;
	Textbox m_textbox;
	sf::Texture m_texField;
	sf::Sprite m_field;

	sf::Vector2u m_score;
	unsigned int m_turns;
	Team m_team_red;
	Team m_team_blue;
	Ball m_ball;

	//////////////////////////////////
	// DEBUG
	bool m_debug;
	sf::Font m_font;
	std::vector<sf::Text> m_reperes;
	//////////////////////////////////

public:

	Game()
		:m_window("Rugby Union Tactics", sf::Vector2u(1856, 866)), m_textbox(sf::Vector2f(1651.f,5.f), sf::Vector2f(200.f, 17*10+10), 100, 14), m_score(0,0), m_turns(NB_TURNS), m_team_red("Red", RED), m_team_blue("Blue", BLUE), m_debug(false) {

		if (!m_texField.loadFromFile("assets/field.png")) {
			std::cout << "Game - Couldn't load texture from file : FIELD" << std::endl;
		}

		m_field.setTexture(m_texField);

	}

	~Game() {}

	static Game * get();

	void init() {
		m_window.setupEvents();
		m_textbox.addMessage("Bindings done.", MessageType::HIGH);

		initDebug();
		m_textbox.addMessage("Debug init.", MessageType::MEDIUM);
	}

	void initDebug() {
		if (!m_font.loadFromFile("assets/arial.ttf")) {
			std::cout << "Game - Couldn't load front from file" << std::endl;
		}

		sf::Text text;
		sf::Vector2u pos;

		text.setCharacterSize(10);
		text.setColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);

		for (unsigned int i = 0; i < 61; i += 3) {
			for (unsigned int j = 0; j < 31; j += 3) {
				pos.x = i;
				pos.y = j;
				text.setPosition(gridToScreen(sf::Vector2u(i, j)) + sf::Vector2f(8.f, 6.f));
				text.setString(std::to_string(i) + "\n" + std::to_string(j));
				m_reperes.push_back(text);
			}
		}
	}

	void updateWorld() {
		m_window.handleEvents();

		// Update world
		// ...
	}

	void render() {
		m_window.clear();

		m_window.draw(m_field);
		m_textbox.draw(m_window);
		m_team_red.draw(m_window);
		m_team_blue.draw(m_window);

		//////////////////////////////////
		// DEBUG
		if (m_debug) {
			for (auto it : m_reperes) {
				it.setFont(m_font);
				m_window.draw(it);
			}
		}
		//////////////////////////////////

		m_window.render();
	}

	bool isTerminated() {
		return m_window.isTerminated();
	}


	//////////////////////// EVENTS ////////////////////////
	void switchDebug(EventDetails * details = nullptr) {
		m_debug = !m_debug;
		if (m_debug)
			m_textbox.addDebugMessage("Grid debug : ON");
		else
			m_textbox.addDebugMessage("Grid debug : OFF");
	}

	void handleMouseClick(EventDetails * details = nullptr) {
		sf::Vector2i w_pos = details->m_mouse;
		sf::Vector2u t_pos = screenToGrid(sf::Vector2f(w_pos));
		m_textbox.addDebugMessage("Click on (" + std::to_string(w_pos.x) + "," + std::to_string(w_pos.y) + ")");
		m_textbox.addDebugMessage("Tile : (" + std::to_string(t_pos.x) + "," + std::to_string(t_pos.y) + ")");

		// Do something
	}

	////////////////////////////////////////////////////////
};
