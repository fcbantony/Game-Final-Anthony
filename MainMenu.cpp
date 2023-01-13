#include "MainMenu.h"

#include <iostream>


//MainMenu::~MainMenu()
//{
//
//}

void MainMenu::draw(sf::RenderWindow& window)
{

	for (int i = 0; i < 3; i++)
	{
		window.draw(mainMenu[i]);
	}

}


void MainMenu::Down() {
	if (optionSelectedMenu + 1 <= Max_Main_Menu)
	{

		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Black);
		optionSelectedMenu++;


		if (optionSelectedMenu == 3)
		{
			optionSelectedMenu = 0;

		}
		std::cout << optionSelectedMenu;
		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Red);

	}
}

void MainMenu::Up() {
	if (optionSelectedMenu - 1 >= -1)
	{
		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Black);
		optionSelectedMenu--;

		if (optionSelectedMenu == -1)
		{
			optionSelectedMenu = 2;
		}
		std::cout << optionSelectedMenu;
		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Red);
	}
}

void MainMenu::clear() {
	mainMenu[0].setFillColor(sf::Color::Transparent);
	mainMenu[1].setFillColor(sf::Color::Transparent);
	mainMenu[2].setFillColor(sf::Color::Transparent);

}

void MainMenu::drawShape(sf::RenderWindow& window, sf::RectangleShape shape) {
	window.draw(shape);
}

void MainMenu::setInventoryMenu(sf::RenderWindow& window) {
	Square1.setPosition(142, 105);
	Square2.setPosition(468, 105);
	Square3.setPosition(795, 105);
	Square4.setPosition(1123, 105);
	Square5.setPosition(1451, 105);

	inventoryScreen.setTexture(textureScreen);
	pickaxe.setTexture(texturePickaxe);
	bow.setTexture(textureBow);
	axe.setTexture(textureAxe);
	grappleHook.setTexture(textureGrappleHook);

	pickaxe.setPosition(170, 115);
	pickaxe.setScale(0.3, 0.2);
	bow.setPosition(510, 106);
	bow.setScale(0.8, 0.75);
	axe.setPosition(810, 95);
	axe.setScale(1.2, 0.75);
	grappleHook.setPosition(1165, 95);
	grappleHook.setScale(0.35, 0.25);

	window.draw(inventoryScreen);
	window.draw(Square1);
	window.draw(Square2);
	window.draw(Square3);
	window.draw(Square4);
	window.draw(Square5);
	window.draw(pickaxe);
	window.draw(bow);
	window.draw(axe);
	window.draw(grappleHook);
}

void MainMenu::changeEquipment(Player& player, sf::Vector2f tracker) {
	if (Square1.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.isPick = true;
		player.isBow = false;
		player.isAxe = false;
		player.isGrappling = false;
		player.animation.coordinates.top = 0;
		inventory = false;
		std::cout << "PICK";
	}

	if (Square2.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.isPick = false;
		player.isBow = true;
		player.isAxe = false;
		player.isGrappling = false;
		player.animation.coordinates.top = 80;
		inventory = false;
		std::cout << "BOW";
	}

	if (Square3.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.isPick = false;
		player.isBow = false;
		player.isAxe = true;
		player.isGrappling = false;
		player.animation.coordinates.top = 160;
		inventory = false;
		std::cout << "AXE";
	}

	if (Square4.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.isPick = false;
		player.isBow = false;
		player.isAxe = false;
		player.isGrappling = true;
		inventory = false;
		std::cout << "GRAPPLING";
	}
}

void MainMenu::mainMenuNavigation(sf::RenderWindow& window) {
	if (keyPressed() == 0) {
		pageNum = 3;
	}
	if (keyPressed() == 1) {
		pageNum = 1;
	}
	if (keyPressed() == 2) {
		window.close();
		pageNum = 2;
	}
}

void MainMenu::setControlsMenu(sf::RenderWindow& window) {

	window.clear();
	sf::Vector2i position = sf::Mouse::getPosition(window);
	sf::Vector2f tracker = window.mapPixelToCoords(position);

	controlsScreen.setTexture(textureControlMenu);

	Square6.setPosition(1605, 835);

	window.draw(controlsScreen);

	if (Square6.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		pageNum = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pageNum == 1) {
		pageNum = 0;
	}

	drawShape(window, Square6);
	window.display();
}

void MainMenu::setMainMenu(sf::RenderWindow& window) {
	mainMenuScreen.setTexture(textureMainMenu);
	window.clear();
	window.draw(mainMenuScreen);
	draw(window);
	window.display();
}

void MainMenu::mainMenuControls(sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pageNum == 0) {
		Down();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pageNum == 0) {
		Up();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && pageNum == 0) {
		mainMenuNavigation(window);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pageNum == 1) {
		pageNum = 0;
	}
}

void MainMenu::setGameOverScreen(sf::RenderWindow& window, Player &player, Level &level) {
	window.clear();
	gameOverScreen.setTexture(textureGameOverScreen);

	sf::Vector2i position = sf::Mouse::getPosition(window);
	sf::Vector2f tracker = window.mapPixelToCoords(position);

	Square7.setPosition(279, 721);
	Square8.setPosition(958, 721);

	window.draw(gameOverScreen);
	window.draw(Square7);
	window.draw(Square8);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Square7.getGlobalBounds().contains(tracker)) {
		player.setHealthToMax();
		level.levelOneComplete = false;
		level.levelTwoComplete = false;
		level.levelThreeComplete = false;
		level.levelSwitch = true;
		level.setMusic("assets/assets_intro.ogg");
		player.setPosition(200, 860);
		pageNum = 0;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Square8.getGlobalBounds().contains(tracker)) {
		window.close();
	}

	window.display();
}

void MainMenu::triggerGameOver(Player player, Level &level) {
	if (player.animation.coordinates.left == 1600 || player.getPlayerHealth().x <= 0) {
		pageNum = 4;
		level.setMusic("assets/assets_death.ogg");
	}
}

void MainMenu::setVictoryScreen(sf::RenderWindow& window, Enemy& enemy, Player& player, Level& level) {
	window.clear();
	victoryScreen.setTexture(textureVictoryScreen);
	sf::Vector2i position = sf::Mouse::getPosition(window);
	sf::Vector2f tracker = window.mapPixelToCoords(position);
	Square7.setPosition(279, 721);
	Square8.setPosition(958, 721);
	Square7.setFillColor(sf::Color::Transparent);
	Square8.setFillColor(sf::Color::Transparent);
	window.draw(victoryScreen);
	window.draw(Square7);
	window.draw(Square8);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Square7.getGlobalBounds().contains(tracker)) {
		level.levelOneComplete = false;
		level.levelTwoComplete = false;
		level.levelThreeComplete = false;
		level.levelSwitch = true;
		level.setMusic("assets/assets_intro.ogg");
		player.setPosition(200, 860);
		pageNum = 0;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Square8.getGlobalBounds().contains(tracker)) {
		window.close();
	}

	window.display();
}

void MainMenu::triggerGameFinished(Level &level) {

	for (int i = 0; i < level.enemies.size(); i++) {
		if (level.enemies[i].getEnemyHealth() <= 0.f && level.levelTwoComplete) {
			pageNum = 5;
			level.setMusic("assets/assets_victory.ogg");
		}
	}

}


