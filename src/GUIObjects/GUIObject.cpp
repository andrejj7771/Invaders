#include "GUIObjects/GUIObject.h"

namespace GUI {
	
	GUIObject::GUIObject(gObj_t type, Scene & scene,
			  const sf::Vector2f & pos) :
		Object(obj_t::gui_object, scene, pos)
	{
		m_gui_type = type;
	}
	
}
