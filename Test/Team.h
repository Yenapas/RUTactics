#pragma once

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "GraphicWindow.h"
#include "Player.h"
#include "globals.h"

class Team
{
private:

	sf::Texture m_texTile;

	std::string m_name;
	unsigned int m_color;
	Player m_players[15];

public:

	Team() {}

	Team(const std::string & name, unsigned int team)
		:m_color(team) {

		if (m_color == RED) {
			if (!m_texTile.loadFromFile("assets/red_tile.png")) {
				std::cout << "Team - Couldn't load texture from file : RED" << std::endl;
			}
		}
		else {
			if (!m_texTile.loadFromFile("assets/blue_tile.png")) {
				std::cout << "Team - Couldn't load texture from file : BLUE" << std::endl;
			}
		}

		for (int i = 0; i<15; ++i) {
			unsigned int index = i + (15 * m_color);
			m_players[i] = Player(	NAM[index], HEI[index], WEI[index], AGE[index],
									MOV[index], ACT[index],
									FOR[index], DEF[index], DEX[index], KIC[index],
									(i + 1), m_color, POS[index], m_texTile);
		}
	}

	~Team() {
		//TODO
	}

	bool selectPlayer(sf::Vector2u pos) {

		for (auto & it : m_players) {
			if (it.getPosition() == pos) {
				for (auto & it2 : m_players)
					it2.select(false);
				it.select();
				return true;
			}
		}
		return false;
	}

	void draw(GraphicWindow & window) {
		for (auto it : m_players) {
			it.draw(window);
		}
	}
};

