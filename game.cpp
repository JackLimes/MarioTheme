#include "game.h"
#include <chrono>
#include <thread>

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

	//loadLevel();
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
		m_mario.draw(m_rWin, m_camera);
		m_mario.move(sf::Vector2i(10, 10));
		m_rWin->display();

		std::this_thread::sleep_until(startTick + frame_duration(1));
	}
}

#include <iostream>
game::~game()
{
	m_rWin->close();
	delete m_rWin;
	m_rWin = nullptr;
}