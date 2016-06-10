#include "GraphicWindow.h"

#include "Game.h"

void GraphicWindow::setupEvents() {
	m_focused = true;

	Game * game = Game::get();
	m_eventManager.addCallback("Debug_toggle", &Game::switchDebug, game);
	m_eventManager.addCallback("Mouse_release", &Game::handleMouseClick, game);

	m_eventManager.addCallback("Window_close", &GraphicWindow::closeEvent, this);
}

void GraphicWindow::handleEvents() {

	sf::Event event;
	while (m_sfWindow.pollEvent(event)) {

		if (event.type == sf::Event::KeyPressed)
			std::cout << "|" << int(event.key.code) << "|" << std::endl;

		if (event.type == sf::Event::LostFocus) {
			m_focused = false;
			m_eventManager.setFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			m_focused = true;
			m_eventManager.setFocus(true);
		}
		m_eventManager.handleEvent(event);
	}
	m_eventManager.update();

	/*Game * game = Game::get();

	while (m_sfWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_terminated = true;
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {
				game->switchDebug();
			}
		}
	}*/
}

void GraphicWindow::closeEvent(EventDetails * details) {
	m_terminated = true;
}