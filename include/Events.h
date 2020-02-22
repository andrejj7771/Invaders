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

template<typename type>
class EventSubscriber {
	
	friend class MouseEvent;
	
public:
	
	EventSubscriber() = default;
	virtual ~EventSubscriber() = default;
	
protected:
	
	virtual void on_event(const type & event) = 0;
	
};

typedef EventSubscriber<MouseState> MouseEventSubscriber;

class MouseEvent {
	
	MouseState m_state;
	std::vector<MouseEventSubscriber*> m_subscribers;
	
	MouseEvent() = default;
	MouseEvent(const MouseEvent & event) = delete;
	MouseEvent & operator=(const MouseEvent & event) = delete;
	
public:
	
	~MouseEvent();
	
	static MouseEvent & instance();
	
	void subscribe(MouseEventSubscriber *subscriber);
	void unsubscribe(MouseEventSubscriber * subscriber);
	
	void update(const sf::RenderWindow & window,
				const sf::Event & event);
	
private:
	
	void update_mouse_state(const sf::RenderWindow & window,
						  const sf::Event & event);
	
};

#endif //EVENTS_H
