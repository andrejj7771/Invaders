#ifndef BUILD_H
#define BUILD_H

#include "GameObject.h"

namespace Game {
	
	class Bullet : public GameObject {
		
	public:
		
		Bullet(const sf::Vector2f & pos);
		~Bullet() override = default;
		
	protected:
		
		void on_draw(sf::RenderWindow & render) override;
		void on_collision(gObj_t type) override;
		void on_update(float time) override;
		
	};
	
}

#endif //BUILD_H
