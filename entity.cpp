#include "entity.h"

void entity::initSprite(
sf::Texture* spriteSheetPtr,
sf::Vector2i texOffset,
sf::Vector2i worldCoords,
int id)
{
	m_worldCoords = worldCoords;
	m_texOffset = texOffset;
	m_entSprite = sf::Sprite(*spriteSheetPtr);
	m_entSprite.setTextureRect(sf::IntRect(m_texOffset.x, m_texOffset.y,
	16, 16));
	m_entSprite.setPosition(m_worldCoords.x, m_worldCoords.y);
	m_id = id;
}


void entity::draw(sf::RenderWindow* win, const sf::Vector2i& cam)
{
	sf::Vector2i pos = m_worldCoords - cam; // Apply camera transform
	m_entSprite.setPosition(pos.x, pos.y);
	win->draw(m_entSprite);
}

sf::Sprite& entity::getSprite()
{
	return m_entSprite; 
}

void entity::setPos(sf::Vector2i newPos)
{
	m_worldCoords = newPos;
}

sf::Vector2i entity::getPos()
{
	return m_worldCoords;
}

void entity::move(sf::Vector2i delta)
{
	m_worldCoords += delta;
}
