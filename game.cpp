#include "game.h"
#include <chrono>
#include <thread>
#include <unistd.h>

typedef std::chrono::duration<int, std::ratio<1, 60>> frame_duration;

game::game()
{
	// Declare window size. The nes was 256x240. ratio 16x15
	// This is sf::Style::Default without resizeability;
	// Plays better with i3-wm this way
	m_rWin = new sf::RenderWindow(sf::VideoMode(256, 240), "MARIO",
	sf::Style::Titlebar | sf::Style::Close);

	m_rWin->setSize(sf::Vector2u(256*3, 240*3)); // upscale for my old eyes.

	// Initialize Sprite sheet
	m_spriteSheet.loadFromFile("mario_tileset.png");

	// Set up mario
	m_mario.initSprite(&m_spriteSheet,
	sf::Vector2i(16, 16), // texture offset
	sf::Vector2i(0, 0), 0); // world coords

	loadLevel();
}

void game::run()
{
	bool endFlag = false;
	sf::Event event;
	while(m_rWin->isOpen() && !endFlag)
	{
		auto startTick = std::chrono::steady_clock::now();
		while(m_rWin->pollEvent(event))
		{
			if(event.type == sf::Event::EventType::Closed)
			{
				endFlag = true;
			}
		}
		// Check for key presses to move mario
		
		
		m_rWin->clear();
		drawBlocks();
		m_mario.draw(m_rWin, m_camera);
		m_mario.move(sf::Vector2i(16, 16));
		m_rWin->display();

		std::this_thread::sleep_until(startTick + frame_duration(1));
	}
}

game::~game()
{
	m_rWin->close();
	delete m_rWin;
	m_rWin = nullptr;
}

void game::loadLevel()
{
	//Hardcoded level
	// TODO accept a string that points to a csv formatted... thing
	m_level = map(15);
	for(int r = 0; r < 15; r++)
	{
		m_level[r] = std::vector<entity>(16);
	}
	for(int c = 0; c < 16; c++)
	{
		entity e;
		e.initSprite(&m_spriteSheet, sf::Vector2i(0, 0), sf::Vector2i(16*c, 16*14), 1);
		m_level[14][c] = e;
	}
}

void game::drawBlocks()
{
	for(int r = 0; r < m_level.size(); r++)
	{
		for(int c = 0; c < m_level[0].size(); c++)
		{
			if(m_level[r][c].id())
			{
				m_level[r][c].draw(m_rWin, m_camera);
			}
		}
	}
}
