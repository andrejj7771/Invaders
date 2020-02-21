#include "GUIObjects/GUIObject.h"

namespace GUI {
	
	GUIEvent::GUIEvent() {
		last_button = sf::Mouse::ButtonCount;
		current_button = sf::Mouse::ButtonCount;
	}
	
	GUIObject::GUIObject(gObj_t type,
			  const sf::Vector2f & pos) :
		Object(obj_t::gui_object, pos),
		m_mouse_enter_handler([](){ printf("MouseEnter default callback\n"); }),
		m_mouse_exit_handler([](){ printf("MouseExit default callback\n"); }),
		m_mouse_stay_handler([](const sf::Vector2f &){ printf("MouseStay default callback\n"); }),
		m_mouse_press_handler([](sf::Mouse::Button){ printf("MousePress default callback\n"); }),
		m_mouse_release_handler([](sf::Mouse::Button){ printf("MouseRelease default callback\n"); })
	{
		m_gui_type = type;
		
		m_is_stay = false;
	}
	
	void GUIObject::on_draw(sf::RenderWindow &window) {
		const sf::Vector2i & window_pos = window.getPosition();
		const sf::Vector2i & mouse_pos = sf::Mouse::getPosition();
		
		sf::Vector2f delta_pos;
		delta_pos.x = std::abs(window_pos.x - mouse_pos.x);
		delta_pos.y = std::abs(window_pos.y - mouse_pos.y) - 40;
		
		const sf::Vector2f & pos = get_position();
		const sf::Vector2f & size = get_size();
		
		bool x = false;
		bool y = false;
		
		if (delta_pos.x >= pos.x && delta_pos.x <= pos.x + size.x) {
			x = true;
		}
		
		if (delta_pos.y >= pos.y && delta_pos.y <= pos.y + size.y) {
			y = true;
		}
		
		if (x && y) {
			if (m_is_stay == false) {
				m_is_stay = true;
				mouse_enter();
			}
			
			if (m_is_stay) {
				mouse_stay(delta_pos);
			}
		} else if ((!x || !y) && m_is_stay){
			m_is_stay = false;
			mouse_exit();
		}
		
		on_gui_draw(window);
	}
	
	void GUIObject::on_update(float) {
		if (m_is_stay) {
			m_event.last_button = m_event.current_button;
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mouse_press(sf::Mouse::Left);
			} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				mouse_press(sf::Mouse::Right);
			} else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
				mouse_press(sf::Mouse::Middle);
			}
			
			if (m_event.last_button != sf::Mouse::ButtonCount) {
				mouse_release(m_event.last_button);
			}
		}
		
		on_gui_update();
	}
	
	void GUIObject::on_destroy() {}
	
}
