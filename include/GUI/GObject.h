#ifndef GUI_OBJECT
#define GUI_OBJECT

#include <functional>

#include "Objects/Object.h"

enum class gui_t : char {
	gui_object = 0,
	label = 1,
	button = 2
};

enum class gEvent_t : char {
	mouse_enter = 0,
	mouse_stay = 1,
	mouse_exit = 2,
	mouse_click = 3
};

namespace GUI {
	
	struct GUIEvent {
		
		gEvent_t type;
		sf::Mouse::Button button;
		
	};
	
	class GUIObject : public Object {
		
		gui_t m_gui_type;
		std::string m_text;
		
		GUIEvent m_event;
		
		std::function<void()> m_mouse_enter_handler;
		std::function<void()> m_mouse_stay_handler;
		std::function<void()> m_mouse_exit_handler;
		std::function<void(sf::Mouse::Button)> m_mouse_click_handler;
		
	public:
		
		GUIObject(gui_t type,
				  const sf::Vector2f & pos = {0, 0},
				  const sf::Vector2f & size = {50, 50});
		
		virtual ~GUIObject() override = default;
		
		inline gui_t get_gui_type() const {
			return m_gui_type;
		}
		
		inline void set_text(const std::string & text) {
			m_text = text;
		}
		
		const std::string & get_text() const {
			return m_text;
		}
		
		inline void set_mouse_enter_callback(const std::function<void()> & callback) {
			m_mouse_enter_handler = callback;
		}
		
		inline void set_mouse_stay_callback(const std::function<void()> & callback) {
			m_mouse_stay_handler = callback;
		}
		
		inline void set_mouse_exit_callback(const std::function<void()> & callback) {
			m_mouse_exit_handler = callback;
		}
		
		inline void set_mouse_click_callback(const std::function<void(sf::Mouse::Button)> & callback) {
			m_mouse_click_handler = callback;
		}
		
	protected:
		
		virtual void on_collision(obj_t type) override;
		virtual void on_update(float time) override;
		virtual void on_gui_update() = 0;
		
	private:
		
		inline void mouse_enter() {
			m_mouse_exit_handler();
		}
		
		inline void mouse_exit() {
			m_mouse_exit_handler();
		}
		
		inline void mouse_stay() {
			m_mouse_stay_handler();
		}
		
		inline void mouse_click(sf::Mouse::Button button) {
			m_mouse_click_handler(button);
		}
		
	};
	
}

#endif //GUI_OBJECT
