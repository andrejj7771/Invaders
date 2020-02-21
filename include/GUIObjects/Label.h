#ifndef LABEL_H
#define LABEL_H

#include "GUIObject.h"

namespace GUI {
	
	class Label;
	typedef std::shared_ptr<Label> LabelPtr;
	
	class Label : public GUIObject {
		
		sf::Text m_text;
		
		uint32_t m_font_size;
		
		bool m_need_update;
		
	public:
		
		Label(const std::string & text,
			  const sf::Font & font,
			  const sf::Vector2f & pos = {0, 0});
		~Label() override = default;
		
		inline void set_font(const sf::Font & font) {
			m_text.setFont(font);
			m_need_update = true;
		}
		
		inline bool set_font(const std::string & font_file) {
			sf::Font font;
			if (!font.loadFromFile(font_file)) {
				return false;
			}
			
			m_text.setFont(font);
			m_need_update = true;
			return true;
		}
		
		inline void set_text(const std::string & text) {
			m_text.setString(sf::String(text));
			m_need_update = true;
		}
		
		inline const std::string & text() const {
			return std::move(m_text.getString().toAnsiString());
		}
		
		inline void set_font_size(uint32_t size) {
			m_text.setCharacterSize(size);
			m_need_update = true;
		}
		
		inline uint32_t font_size() const {
			return m_text.getCharacterSize();
		}
		
		inline void set_text_color(const sf::Color & color) {
			m_text.setFillColor(color);
		}
		
		inline const sf::Color & text_color() const {
			return m_text.getFillColor();
		}
		
		inline void set_style(uint32_t style) {
			m_text.setStyle(style);
			m_need_update = true;
		}
		
		inline uint32_t style_flag() const {
			return m_text.getStyle();
		}
		
	protected:
		
		virtual void on_gui_update() override;
		virtual void on_gui_draw(sf::RenderWindow & window) override;
		
	};
	
}

#endif //LABEL_H
