#include "GUI/GObject.h"

namespace GUI {
	
	GUIObject::GUIObject(gui_t type,
			  const sf::Vector2f & pos,
			  const sf::Vector2f & size) :
		Object(obj_t::gui, pos),
		m_mouse_enter_handler([](){}),
		m_mouse_stay_handler([](){}),
		m_mouse_exit_handler([](){}),
		m_mouse_click_handler([](sf::Mouse::Button){})
	{
		m_gui_type = type;
		set_size(size);
	}
	
	
	void GUIObject::on_collision(obj_t) {}
	
	void GUIObject::on_update(float time) {
		
	}
	
}
