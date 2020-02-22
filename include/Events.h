#ifndef EVENTS_H
#define EVENTS_H

#include <memory>

#include <SFML/Graphics.hpp>

struct MouseState {
	
	sf::Mouse::Button button;
	sf::Vector2f pos;
	sf::Event::EventType button_state;
	
	MouseState();
	
};

class MouseEvent;

class EventSubscriber {
	
	friend class MouseEvent;
	
public:
	
	EventSubscriber() = default;
	virtual ~EventSubscriber() = default;
	
protected:
	
	virtual void on_event(const MouseState & e) = 0;
	
};

class MouseEvent {
	
	MouseState m_state;
	std::vector<EventSubscriber *> m_subscribers;
	
	MouseEvent() = default;
	MouseEvent(const MouseEvent & event) = delete;
	MouseEvent & operator=(const MouseEvent & event) = delete;
	
public:
	
	~MouseEvent();
	
	static MouseEvent & instance();
	
	void subscribe(EventSubscriber *subscriber);
	void unsubscribe(EventSubscriber * subscriber);
	
	void update(const sf::RenderWindow & window,
				const sf::Event & event);
	
private:
	
	void update_mouse_state(const sf::RenderWindow & window,
						  const sf::Event & event);
	
};

#endif //EVENTS_H
