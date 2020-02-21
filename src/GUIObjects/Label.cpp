#include "GUIObjects/Label.h"

namespace GUI {
	
	Label::Label(const std::string & text,
				 const sf::Font & font,
				 const sf::Vector2f & pos) :
		GUIObject(gObj_t::label, pos)
	{
		set_font(font);
		set_text(text);
		m_text.setPosition(pos);
	}
	
	void Label::on_destroy() {}
	
	void Label::on_update(float) {
		const sf::FloatRect & rect = m_text.getLocalBounds();
		m_text.setPosition(get_position());
		set_size(sf::Vector2f(rect.width + rect.left, rect.height + rect.top * 2));
	}
	
	void Label::on_draw(sf::RenderWindow & window) {
		window.draw(m_shape);
		window.draw(m_text);
	}
	
}
