#ifndef GAME_H
#define GAME_H
#include "entity.h"

#include <SFML/Graphics.hpp>
#include <vector>


typedef std::vector<std::vector<entity>> map;

class game
{
	private:
		sf::RenderWindow* m_rWin;
		sf::Texture m_spriteSheet;
		sf::Vector2i m_camera;
		map m_level;
		
		entity m_mario;
	public:
		~game();
		game();
		void run();
		void loadLevel();
		void drawBlocks();
};
#endif
