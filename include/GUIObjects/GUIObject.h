#ifndef GUI_OBJECT
#define GUI_OBJECT

#include <functional>

#include "Object.h"

namespace GUI {
	
	enum class gObj_t : char {
		gui_object = 0,
		label = 1,
		button = 2
	};
	
	class GUIObject;
	typedef std::shared_ptr<GUIObject> GUIObjectPtr;
	
	class GUIObject : public Object {
		
	protected:
		
		gObj_t m_gui_type;
		
	public:
		
		GUIObject(gObj_t type, Scene & scene,
				  const sf::Vector2f & pos = {0, 0});
		
		virtual ~GUIObject() override = default;
		
		inline gObj_t get_gui_type() const {
			return m_gui_type;
		}
		
	};
	
}

#endif //GUI_OBJECT
