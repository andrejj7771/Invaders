#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
#include "Events.h"

namespace GUI {
	
	enum class gEvent_t : char {
		mouse_enter = 0,
		mouse_stay = 1,
		mouse_exit = 2,
		mouse_press = 3,
		mouse_release = 4
	};
	
	struct GUIEvent {
		
		gEvent_t type;
		sf::Mouse::Button current_button;
		sf::Mouse::Button last_button;
		
		GUIEvent();
		
	};
	
	class Button;
	typedef std::shared_ptr<Button> ButtonPtr;
	
	class Button : public Label, public MouseEventSubscriber {
		
		GUIEvent m_event;
		
		bool m_is_stay;
		bool m_is_pressed;
		
		std::function<void()> m_mouse_enter_handler;
		std::function<void()> m_mouse_exit_handler;
		std::function<void(const sf::Vector2f & pos)> m_mouse_stay_handler;
		std::function<void(sf::Mouse::Button)> m_mouse_pressed_handler;
		std::function<void(sf::Mouse::Button)> m_mouse_released_handler;
		
	public:
		
		Button(Scene & scene,
			   const std::string & text,
			   const sf::Font & font,
			   const sf::Vector2f & pos = {0, 0});
		~Button() override;
		
		inline void set_mouse_enter_callback(const std::function<void()> & callback) {
			m_mouse_enter_handler = callback;
		}
		
		inline void set_mouse_exit_callback(const std::function<void()> & callback) {
			m_mouse_exit_handler = callback;
		}
		
		inline void set_mouse_stay_callback(const std::function<void(const sf::Vector2f & pos)> & callback) {
			m_mouse_stay_handler = callback;
		}
		
		inline void set_mouse_pressed_callback(const std::function<void(sf::Mouse::Button)> & callback) {
			m_mouse_pressed_handler = callback;
		}
		
		inline void set_mouse_released_callback(const std::function<void(sf::Mouse::Button)> & callback) {
			m_mouse_released_handler = callback;
		}
		
	protected:
		
		void on_destroy() override;
		void on_event(const MouseState & state) override;
		
	};
	
}

#endif //BUTTON_H
