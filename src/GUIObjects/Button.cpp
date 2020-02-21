#include "GUIObjects/Button.h"

namespace GUI {
	
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
	}
	
	void Button::on_draw(sf::RenderWindow & window) {
		Label::on_draw(window);
		
		const sf::Vector2i & window_pos = window.getPosition();
		const sf::Vector2i & mouse_pos = sf::Mouse::getPosition();
		
		sf::Vector2f delta_pos;
		delta_pos.x = std::abs(window_pos.x - mouse_pos.x);
		delta_pos.y = std::abs(window_pos.y - mouse_pos.y) - 40;
		
		const sf::Vector2f & pos = get_position();
		const sf::Vector2f & size = get_size();
		
		bool x = false;
		if (delta_pos.x >= pos.x && delta_pos.x <= pos.x + size.x) {
			x = true;
		}
		
		bool y = false;
		if (delta_pos.y >= pos.y && delta_pos.y <= pos.y + size.y) {
			y = true;
		}
		
		if (x && y) {
			if (m_is_stay == false) {
				m_mouse_enter_handler();
			}
			
			m_is_stay = true;
			m_mouse_stay_handler({static_cast<float>(mouse_pos.x),
								  static_cast<float>(mouse_pos.y)});
		} else {
			if (m_is_stay == true) {
				m_mouse_exit_handler();
			}
			m_is_stay = false;
		}
	}
	
	void Button::on_destroy() {}
	
	void Button::on_update(float time) {
		Label::on_update(time);
		
		if (m_is_stay == true && m_is_pressed == false) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mouse_press(sf::Mouse::Left);
			} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				mouse_press(sf::Mouse::Right);
			} else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
				mouse_press(sf::Mouse::Middle);
			}
		}
	}
	
}
