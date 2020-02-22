#include "GUIObjects/Button.h"

namespace GUI {
	
	GUIEvent::GUIEvent() {
		last_button = sf::Mouse::ButtonCount;
		current_button = sf::Mouse::ButtonCount;
	}
	
	Button::Button(const std::string & text,
				   const sf::Font & font,
				   const sf::Vector2f & pos) :
		Label(text, font, pos),
		m_mouse_enter_handler([](){}),
		m_mouse_exit_handler([](){}),
		m_mouse_stay_handler([](const sf::Vector2f &){}),
		m_mouse_press_handler([](sf::Mouse::Button){}),
		m_mouse_release_handler([](sf::Mouse::Button){})
	{
		m_gui_type = gObj_t::button;
		m_is_stay = false;
		m_is_pressed = false;
		
		MouseEvent::instance().subscribe(this);
	}
	
	Button::~Button() {
		MouseEvent::instance().unsubscribe(this);
	}
	
	void Button::on_destroy() {
		MouseEvent::instance().unsubscribe(this);
	}
	
	void Button::on_event(const MouseState & state) {
		const sf::Vector2f & pos = get_position();
		const sf::Vector2f & size = get_size();
		
		bool x = false;
		if (state.pos.x >= pos.x && state.pos.x <= pos.x + size.x) {
			x = true;
		}
		
		bool y = false;
		if (state.pos.y >= pos.y && state.pos.y <= pos.y + size.y) {
			y = true;
		}
		
		if (x && y) {
			if (m_is_stay == false) {
				m_mouse_enter_handler();
			}
			
			m_is_stay = true;
			m_mouse_stay_handler(state.pos);
		} else {
			if (m_is_stay == true) {
				m_mouse_exit_handler();
			}
			m_is_stay = false;
		}
		
		if (m_is_stay) {
			if (state.button_state == sf::Event::MouseButtonPressed) {
				m_mouse_press_handler(state.button);
			} else if (state.button_state == sf::Event::MouseButtonReleased) {
				m_mouse_release_handler(state.button);
			}
		}
	}
	
}
