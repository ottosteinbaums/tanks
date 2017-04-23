#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "stdafx.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

int main()
{
	// Define some constants
	const float pi = 3.14159f;
	const int gameWidth = 800;
	const int gameHeight = 600;
	sf::Vector2f paddleSize(25, 100);
	float ballRadius = 10.f;
	const float manSpeed = 400.f;

	// Create tiny man
	sf::RectangleShape tiny_man;
	tiny_man.setSize(sf::Vector2f(3,3));
	tiny_man.setOutlineThickness(3);
	tiny_man.setOutlineColor(sf::Color::Black);
	tiny_man.setFillColor(sf::Color::Red);
	tiny_man.setOrigin(sf::Vector2f(3,3));

	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Spoopy gem",
		sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;

	// Initialize the pause message
	sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(170.f, 150.f);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("ENTER the spoop");
	window.display();

	sf::Clock clock;
	bool isPlaying = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return))
			{
				if (!isPlaying)
				{
					isPlaying = true;
					clock.restart();
					tiny_man.setPosition(gameHeight / 2, gameWidth / 2);
				}
			}
		}
		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();
			//Move up
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				(tiny_man.getPosition().y - 20.f / 2 > 5.f))
			{
				tiny_man.move(0.f, -manSpeed * deltaTime);
				if (tiny_man.getPosition().y < 5.f) {
					tiny_man.setPosition(tiny_man.getPosition().x, 5.f);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				(tiny_man.getPosition().y + 20.f < gameHeight - 5.f))
			{
				tiny_man.move(0.f, manSpeed * deltaTime);
				if (tiny_man.getPosition().y > gameHeight - 5.f) {
					tiny_man.setPosition(tiny_man.getPosition().x, gameHeight - 5.f);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
				(tiny_man.getPosition().x > 5.f))
			{
				tiny_man.move(-manSpeed * deltaTime, 0.f);
				if (tiny_man.getPosition().x < 5.f) {
					tiny_man.setPosition(5.f, tiny_man.getPosition().y);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
				(tiny_man.getPosition().x < gameWidth - 5.f))
			{
				tiny_man.move(manSpeed * deltaTime, 0.f);
				if (tiny_man.getPosition().x > gameWidth - 5.f) {
					tiny_man.setPosition(gameWidth - 5.f,tiny_man.getPosition().y);
				}
			}

		}
		window.clear(sf::Color::Black);
		if (isPlaying)
		{
			window.draw(tiny_man);
		}
		else
		{
			window.draw(pauseMessage);
		}
		window.display();
	}

}

