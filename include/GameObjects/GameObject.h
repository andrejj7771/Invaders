#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Object.h"

namespace Game {
	
	enum class gObj_t : uint8_t {
		game_object = 0,
		player = 1,
		enemy = 2,
		bullet = 3
	};
	
	class GameObject;
	typedef std::shared_ptr<GameObject> GameObjectPtr;
	
	class GameObject : public Object {
		
	protected:
		
		gObj_t m_object_type;
		
	public:
		
		GameObject(gObj_t obj_type, const sf::Vector2f & pos = {0, 0});
		virtual ~GameObject() override = default;
		
		inline gObj_t game_object_type() const {
			return m_object_type;
		}
		
		///
		/// \brief check_collision - collision checker with other object
		/// \param object - object that will be checked
		/// \return true if objects are intersected, otherwise - false
		///
		inline bool check_collision(const GameObjectPtr & object) {
			assert(object != nullptr);
			
			sf::Rect<float> rect_1(get_position(), get_size());
			sf::Rect<float> rect_2(object->get_position(), object->get_size());
			
			bool is_intersects = rect_1.intersects(rect_2);
			if (is_intersects) {
				on_collision(object->game_object_type());
			}
			
			return is_intersects;
		}
		
	protected:
		
		///
		/// \brief on_collision - collision solver
		/// \param type - type of the object that is collided with this object
		///
		virtual void on_collision(gObj_t obj) = 0;
		
		virtual void on_destroy() override;
		
	};
	
}

#endif //GAME_OBJECT_H
