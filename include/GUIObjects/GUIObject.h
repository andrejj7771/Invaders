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
	
	enum class gEvent_t : char {
		mouse_enter = 0,
		mouse_stay = 1,
		mouse_exit = 2,
		mouse_press = 3,
		mouse_release = 4
	};
	
	class GUIObject;
	typedef std::shared_ptr<GUIObject> GUIObjectPtr;
	
	struct GUIEvent {
		
		gEvent_t type;
		sf::Mouse::Button current_button;
		sf::Mouse::Button last_button;
		
		GUIEvent();
		
	};
	
	class GUIObject : public Object {
		
		gObj_t m_gui_type;
		
		GUIEvent m_event;
		
		std::function<void()> m_mouse_enter_handler;
		std::function<void()> m_mouse_exit_handler;
		std::function<void(const sf::Vector2f & pos)> m_mouse_stay_handler;
		std::function<void(sf::Mouse::Button)> m_mouse_press_handler;
		std::function<void(sf::Mouse::Button)> m_mouse_release_handler;
		
		bool m_is_stay;
		
	public:
		
		GUIObject(gObj_t type,
				  const sf::Vector2f & pos = {0, 0});
		
		virtual ~GUIObject() override = default;
		
		inline gObj_t get_gui_type() const {
			return m_gui_type;
		}
		
		inline void set_mouse_enter_callback(const std::function<void()> & callback) {
			m_mouse_enter_handler = callback;
		}
		
		inline void set_mouse_exit_callback(const std::function<void()> & callback) {
			m_mouse_exit_handler = callback;
		}
		
		inline void set_mouse_stay_callback(const std::function<void(const sf::Vector2f & pos)> & callback) {
			m_mouse_stay_handler = callback;
		}
		
		inline void set_mouse_click_callback(const std::function<void(sf::Mouse::Button)> & callback) {
			m_mouse_press_handler = callback;
		}
		
	protected:
		
		virtual void on_draw(sf::RenderWindow & window) override;
		virtual void on_update(float time) override;
		virtual void on_destroy() override;
		
		virtual void on_gui_update() = 0;
		virtual void on_gui_draw(sf::RenderWindow & window) = 0;
		
	private:
		
		
		inline void mouse_enter() {
			m_mouse_exit_handler();
		}
		
		inline void mouse_exit() {
			m_mouse_exit_handler();
		}
		
		inline void mouse_stay(const sf::Vector2f & pos) {
			m_mouse_stay_handler(pos);
		}
		
		inline void mouse_press(sf::Mouse::Button button) {
			m_mouse_press_handler(button);
		}
		
		inline void mouse_release(sf::Mouse::Button button) {
			m_mouse_release_handler(button);
		}
		
	};
	
}

#endif //GUI_OBJECT
