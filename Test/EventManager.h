#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

enum class EventType {
	KeyDown		= sf::Event::KeyPressed,
	KeyUp		= sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp	= sf::Event::MouseButtonReleased,
	MouseWheel	= sf::Event::MouseWheelMoved,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus	= sf::Event::LostFocus,
	Closed		= sf::Event::Closed,
	Keyboard	= sf::Event::Count + 1,
	Mouse
};

struct EventInfo {
	union {
		int m_code;
	};

	EventInfo() {
		m_code = 0;
	}

	EventInfo(int event) {
		m_code = event;
	}
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails {
	std::string m_name;
	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode;

	EventDetails(const std::string & bindName)
		:m_name(bindName) {
		clear();
	}

	void clear() {
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

struct Binding {
	Events m_events;
	std::string m_name;
	int c;
	EventDetails m_details;

	Binding(const std::string & name)
		:m_name(name), m_details(name), c(0) {}

	void bindEvent(EventType type, EventInfo info = EventInfo()) {
		m_events.emplace_back(type, info);
	}
};

using Bindings = std::unordered_map<std::string, Binding *>;

using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

class EventManager
{
private:

	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_hasFocus;

	void loadBindings();

public:
	EventManager();
	~EventManager();

	bool addBinding(Binding * binding);

	bool removeBinding(std::string name);

	void setFocus(const bool & focus);

	template <class T>
	bool addCallback(const std::string & name, void(T::*func)(EventDetails *), T * instance) {
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return m_callbacks.emplace(name, temp).second;
	}

	void removeCallback(const std::string & name) {
		m_callbacks.erase(name);
	}

	void handleEvent(sf::Event & event);

	void update();

	/*sf::Vector2i getMousePos(sf::RenderWindow * window = nullptr) {
		return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
	}*/
};

