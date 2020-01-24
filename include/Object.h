#ifndef OBJECT_H
#define OBJECT_H

#include <cassert>
#include <memory>

#include <SFML/Graphics.hpp>

enum class obj_t : uint8_t {
	object = 0,
	player = 1,
	enemy = 2,
	bullet = 3
};

class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class Object {
	
	obj_t m_type;
	
	bool m_visible;
	bool m_need_destroy;
	
	sf::RectangleShape m_shape;
	
public:
	
	Object(obj_t type, const sf::Vector2f & pos = {0, 0});
	virtual ~Object() = default;
	
	inline const sf::RectangleShape & shape() const {
		return m_shape;
	}
	
	inline void draw(sf::RenderWindow & render) {
		if (m_visible == false) {
			return;
		}
		
		if (m_need_destroy == true) {
			return;
		}
		
		on_draw(render);
	}
	
	inline void update(float time) {
		if (m_need_destroy == true ||
				m_visible == false)
		{
			return;
		}
		
		on_update(time);
	}
	
	inline void destroy() {
		if (m_need_destroy == true) {
			return;
		}
		
		on_destroy();
		m_need_destroy = true;
	}
	
	inline bool is_destroyed() const {
		return m_need_destroy;
	}
	
	inline void set_visible(bool visible = true) {
		m_visible = visible;
	}
	
	inline bool is_visible() const {
		return m_visible;
	}
	
	inline bool check_collision(const ObjectPtr & object) {
		assert(object != nullptr);
		
		sf::Rect<float> rect_1(get_position(), get_size());
		sf::Rect<float> rect_2(object->get_position(), object->get_size());
		
		bool is_intersects = rect_1.intersects(rect_2);
		if (is_intersects) {
			on_collision(object->get_type());
		}
		
		return is_intersects;
	}
	
	inline obj_t get_type() const {
		return m_type;
	}
	
	inline void set_size(const sf::Vector2f & size = {50, 50}) {
		m_shape.setSize(size);
	}
	
	inline const sf::Vector2f & get_size() const {
		return m_shape.getSize();
	}
	
	inline void set_position(const sf::Vector2f & pos = {0, 0}) {
		m_shape.setPosition(pos);
	}
	
	inline const sf::Vector2f & get_position() const {
		return m_shape.getPosition();
	}
	
	inline void set_scale(const sf::Vector2f & factor = {1, 1}) {
		m_shape.setScale(factor);
	}
	
	inline const sf::Vector2f & get_scale() const {
		return m_shape.getScale();
	}
	
	inline void set_fill_color(const sf::Color & color = sf::Color::White) {
		m_shape.setFillColor(color);
	}
	
	inline const sf::Color & get_fill_color() const {
		return m_shape.getFillColor();
	}
	
	inline void set_texture(const sf::Texture & texture) {
		m_shape.setTexture(&texture);
	}
	
	inline const sf::Texture & get_texture() const {
		return *m_shape.getTexture();
	}
	
protected:
	
	virtual void on_collision(obj_t type) = 0;
	virtual void on_draw(sf::RenderWindow & render) = 0;
	virtual void on_destroy() {}
	virtual void on_update(float time) = 0;
	
};


#endif //OBJECT_H
