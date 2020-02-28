#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class entity
{
	private:
		sf::Vector2<int> m_worldCoords;
		sf::Vector2<int> m_texOffset;
		sf::Sprite m_entSprite;
		int m_id = 0;

	public:
		void initSprite(
		sf::Texture* spriteSheetPtr,
		sf::Vector2i texOffset,
		sf::Vector2i worldCoords,
		int id);

		sf::Sprite& getSprite();
		void draw(sf::RenderWindow* win, const sf::Vector2i& cam);
		void setPos(sf::Vector2i newPos);
		sf::Vector2i getPos();
		void move(sf::Vector2i delta);
		int id() { return m_id;}
};


#endif
