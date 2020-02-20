#ifndef OBJECT_H
#define OBJECT_H

#include <cassert>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Components/Component.h"
#include "Components/ComponentFactory.h"

enum class obj_t : uint8_t {
	object = 0,
	player = 1,
	enemy = 2,
	bullet = 3,
	gui = 4
};

class Object;
typedef std::shared_ptr<Object> ObjectPtr;

typedef std::shared_ptr<Component> ComponentPtr;

class Object {
	
	///
	/// \brief m_type - object type, see obj_t enum values
	///
	obj_t m_type;
	
	///
	/// \brief m_visible - visible state flag
	///
	bool m_visible;
	
	///
	/// \brief m_need_destroy - flag that indicates that object must be destroyed
	///
	bool m_need_destroy;
	
	///
	/// \brief m_shape - shape of the object
	///
	sf::RectangleShape m_shape;
	
	///
	/// \brief m_components - component list of the object
	///
	std::vector<ComponentPtr> m_components;
	
public:
	
	Object(obj_t type, const sf::Vector2f & pos = {0, 0});
	virtual ~Object() = default;
	
	///
	/// \brief shape - getter of animation shape
	/// \return instance of the shape object
	///
	inline const sf::RectangleShape & shape() const {
		return m_shape;
	}
	
	///
	/// \brief draw - draw object on the screen
	/// \param render - renderer instance
	///
	inline void draw(sf::RenderWindow & render) {
		if (m_visible == false) {
			return;
		}
		
		if (m_need_destroy == true) {
			return;
		}
		
		on_draw(render);
	}
	
	///
	/// \brief update - object updater
	/// \param time - elapsed time from last frame
	///
	inline void update(float time) {
		if (m_need_destroy == true ||
				m_visible == false)
		{
			return;
		}
		
		for (auto component : m_components) {
			component->update(time);
		}
		
		on_update(time);
	}
	
	///
	/// \brief destroy - object destroyer
	///
	inline void destroy() {
		if (m_need_destroy == true) {
			return;
		}
		
		on_destroy();
		m_need_destroy = true;
	}
	
	///
	/// \brief is_destroyed - getter of destroy state value
	/// \return true - object will be destroyed on the next update iteration
	///
	inline bool is_destroyed() const {
		return m_need_destroy;
	}
	
	///
	/// \brief set_visible - setter of the visibility state
	/// \param visible - true - obejct won't be rendered, false - object will be rendered
	///
	inline void set_visible(bool visible = true) {
		m_visible = visible;
	}
	
	///
	/// \brief is_visible - getter of visibility state of the object
	/// \return boolean value of visibility state
	///
	inline bool is_visible() const {
		return m_visible;
	}
	
	///
	/// \brief check_collision - collision checker with other object
	/// \param object - object that will be checked
	/// \return true if objects are intersected, otherwise - false
	///
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
	
	///
	/// \brief get_type - getter of object type
	/// \return enum value of type
	///
	inline obj_t get_type() const {
		return m_type;
	}
	
	inline void set_size(const sf::Vector2f & size = {50, 50}) {
		m_shape.setSize(size);
	}
	
	/*--------------------------------------------------------------------*/
	
	///
	/// \brief this methods use SFML methods, see SFML documentation
	///
	
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
	
	/*--------------------------------------------------------------------*/
	
	///
	/// \brief add_component - add new component to object
	/// \param type - compoent type
	/// \return component instance
	///
	inline ComponentPtr add_component(component_t type) {
		ComponentPtr component = get_component(type);
		if (component != nullptr) {
			return component;
		}
		
		component = ComponentFactory::create(type, this);
		if (component == nullptr) {
			return nullptr;
		}
		
		m_components.push_back(component);
		return component;
	}
	
	///
	/// \brief has_component - check for component availability
	/// \param type - component type
	/// \return true is component is available
	///
	inline bool has_component(component_t type) const {
		auto find_predicate = [type](const ComponentPtr & c)
		{
			return c->get_type() == type;
		};
		
		auto c_iterator = std::find_if(m_components.begin(),
									   m_components.end(),
									   find_predicate);
		
		return c_iterator != m_components.end();
	}
	
	///
	/// \brief get_component - getter of the component by type
	/// \param type - type of the component
	/// \return component instance if component is available, otherwise - nullptr
	///
	inline ComponentPtr get_component(component_t type) {
		auto find_predicate = [type](const ComponentPtr & c)
		{
			return c->get_type() == type;
		};
		
		auto c_iterator = std::find_if(m_components.begin(),
									   m_components.end(),
									   find_predicate);
		
		if (c_iterator == m_components.end()) {
			return nullptr;
		}
		
		return *c_iterator;
	}
	
	///
	/// \brief rem_component - remove comonent by type
	/// \param type - type of the component
	///
	inline void rem_component(component_t type) {
		auto find_predicate = [type](const ComponentPtr & c)
		{
			return c->get_type() == type;
		};
		
		auto c_iterator = std::find_if(m_components.begin(),
									   m_components.end(),
									   find_predicate);
		
		if (c_iterator != m_components.end()) {
			m_components.erase(c_iterator);
		}
	}
	
	///
	/// \brief get_num_components - get number of the components
	/// \return number of the components
	///
	inline size_t get_num_components() const {
		return m_components.size();
	}
	
protected:
	
	///
	/// \brief on_collision - collision solver
	/// \param type - type of the object that is collided with this object
	///
	virtual void on_collision(obj_t type) = 0;
	
	///
	/// \brief on_draw - concrete object drawer
	/// \param render - instance of the renderer
	///
	virtual void on_draw(sf::RenderWindow & render) = 0;
	
	///
	/// \brief on_destroy - concrete destroyer
	///
	virtual void on_destroy() {}
	
	///
	/// \brief on_update - concrete updater
	/// \param time - elapsed time from last frame
	///
	virtual void on_update(float time) = 0;
	
};


#endif //OBJECT_H
