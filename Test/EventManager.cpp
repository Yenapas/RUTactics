#include "EventManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

EventManager::EventManager()
	:m_hasFocus(true) {
	loadBindings();
}

EventManager::~EventManager() {
	for (auto & itr : m_bindings) {
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::addBinding(Binding * binding) {

	std::cout << "(" << binding->m_name << ",[";
	for (auto & it : binding->m_events) {
		std::cout << int(it.first) << ":" << it.second.m_code << ",";
	}
	std::cout << "])" << std::endl;

	if (m_bindings.find(binding->m_name) != m_bindings.end())
		return false;

	return m_bindings.emplace(binding->m_name, binding).second;
}

bool EventManager::removeBinding(std::string name) {
	auto itr = m_bindings.find(name);

	if (itr == m_bindings.end())
		return false;

	delete itr->second;
	m_bindings.erase(itr);
	return true;
}


void EventManager::setFocus(const bool & focus) {
	m_hasFocus = focus;
}

void EventManager::handleEvent(sf::Event & event) {
	for (auto & bind_itr : m_bindings) {
		Binding * binding = bind_itr.second;

		for (auto & event_itr : binding->m_events) {
			EventType sfmlEvent = (EventType)event.type;

			if (event_itr.first != sfmlEvent)
				continue;

			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
				if (event_itr.second.m_code == event.key.code) {
					if (binding->m_details.m_keyCode != -1) {
						binding->m_details.m_keyCode = event_itr.second.m_code;
					}
					++(binding->c);
					break;
				}
			} else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
				if (event_itr.second.m_code == event.mouseButton.button) {
					binding->m_details.m_mouse.x = event.mouseButton.x;
					binding->m_details.m_mouse.y = event.mouseButton.y;
					if (binding->m_details.m_keyCode != -1) {
						binding->m_details.m_keyCode = event_itr.second.m_code;
					}
					++(binding->c);
					break;
				}
			} else {
				if (sfmlEvent == EventType::MouseWheel) {
					binding->m_details.m_mouseWheelDelta = event.mouseWheel.delta;
				}
				++(binding->c);
			}
		}
	}
}

void EventManager::update() {
	if (!m_hasFocus)
		return;

	for (auto & bind_itr : m_bindings) {
		Binding * binding = bind_itr.second;
		
		for (auto & event_itr : binding->m_events) {
			switch (event_itr.first) {
			case EventType::Keyboard :
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(event_itr.second.m_code))) {
					if (binding->m_details.m_keyCode != -1) {
						binding->m_details.m_keyCode = event_itr.second.m_code;
					}
					++(binding->c);
				}
				break;
			case EventType::Mouse :
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(event_itr.second.m_code))) {
					if (binding->m_details.m_keyCode != -1) {
						binding->m_details.m_keyCode = event_itr.second.m_code;
					}
					++(binding->c);
				}
				break;
			default :
				break;
			}

			if (binding->m_events.size() == binding->c) {
				auto call_itr = m_callbacks.find(binding->m_name);
				if (call_itr != m_callbacks.end()) {
					call_itr->second(&binding->m_details);
				}
				binding->c = 0;
				binding->m_details.clear();
			}
		}
	}
}

void EventManager::loadBindings() {
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("assets/keys.cfg");
	if (!bindings.is_open()) {
		std::cout << "EventManager - Couldn't open config file" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;

		Binding * binding = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			int start = 0, end = keyval.find(delimiter);
			if (end == std::string::npos) {
				delete binding;
				binding = nullptr;
				break;
			}
			EventType type = EventType(stoi(keyval.substr(start, end - start)));
			int code = stoi(keyval.substr(end + delimiter.length(), keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.m_code = code;

			binding->bindEvent(type, eventInfo);
		}

		if (!addBinding(binding)) {
			delete binding;
		}
		binding = nullptr;
	}
	bindings.close();
}