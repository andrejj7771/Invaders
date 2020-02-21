#include "GUIObjects/GUIObject.h"

namespace GUI {
	
	GUIEvent::GUIEvent() {
		last_button = sf::Mouse::ButtonCount;
		current_button = sf::Mouse::ButtonCount;
	}
	
	GUIObject::GUIObject(gObj_t type,
			  const sf::Vector2f & pos) :
		Object(obj_t::gui_object, pos)
	{
		m_gui_type = type;
	}
	
}
