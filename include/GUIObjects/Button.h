#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"

namespace GUI {
	
	class Button;
	typedef std::shared_ptr<Button> ButtonPtr;
	
	class Button : public Label {
		
		bool m_is_stay;
		bool m_pressed;
		GUIEvent m_event;
		
		std::function<void()> m_mouse_enter_handler;
		std::function<void()> m_mouse_exit_handler;
		std::function<void(const sf::Vector2f & pos)> m_mouse_stay_handler;
		std::function<void(sf::Mouse::Button)> m_mouse_press_handler;
		std::function<void(sf::Mouse::Button)> m_mouse_release_handler;
		
	public:
		
		Button(const std::string & text,
			   const sf::Font & font,
			   const sf::Vector2f & pos = {0, 0});
		~Button() override = default;
		
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
		
		void on_destroy() override;
		void on_update(float time) override;
		void on_draw(sf::RenderWindow & window) override;
		
	private:
		
		inline void mouse_press(sf::Mouse::Button button) {
			if (m_pressed == false) {
				m_pressed = true;
				m_mouse_press_handler(button);
			}
		}
		
		inline void mouse_release(sf::Mouse::Button button) {
			m_mouse_release_handler(button);
			m_pressed = false;
		}
		
	};
	
}

#endif //BUTTON_H
