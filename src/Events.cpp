#include "Events.h"

#include <cassert>

MouseState::MouseState() :
	button(sf::Mouse::ButtonCount),
	pos({0, 0})
{
	button_state = sf::Event::Count;
}

MouseEvent::~MouseEvent() {
	m_subscribers.clear();
}

MouseEvent & MouseEvent::instance() {
	static MouseEvent _instance;
	return _instance;
}

void MouseEvent::subscribe(MouseEventSubscriber * subscriber) {
	assert(subscriber != nullptr);
	
	auto it = std::find(m_subscribers.begin(), m_subscribers.end(), subscriber);
	if (it != m_subscribers.end()) {
		return;
	}
	
	m_subscribers.push_back(subscriber);
}

void MouseEvent::unsubscribe(MouseEventSubscriber * subscriber) {
	assert(subscriber != nullptr);
	
	auto it = std::find(m_subscribers.begin(), m_subscribers.end(), subscriber);
	if (it == m_subscribers.end()) {
		return;
	}
	
	m_subscribers.erase(it);
}

void MouseEvent::update(const sf::RenderWindow & window,
						const sf::Event & event)
{
	update_mouse_state(window, event);
	
	for (auto subscriber : m_subscribers) {
		subscriber->on_event(m_state);
	}
}

void MouseEvent::update_mouse_state(const sf::RenderWindow & window,
								  const sf::Event & event)
{
	const sf::Vector2i & mouse_pos = sf::Mouse::getPosition(window);
	m_state.pos = sf::Vector2f(static_cast<float>(mouse_pos.x),
							   static_cast<float>(mouse_pos.y));
	
	if (event.type == sf::Event::MouseButtonPressed) {
		m_state.button_state = sf::Event::MouseButtonPressed;
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			m_state.button = sf::Mouse::Left;
		} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			m_state.button = sf::Mouse::Right;
		} else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
			m_state.button = sf::Mouse::Middle;
		}
	} else if (event.type == sf::Event::MouseButtonReleased) {
		m_state.button_state = sf::Event::MouseButtonReleased;
	}
}

