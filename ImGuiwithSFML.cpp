// ImGuiwithSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include "Player.h"
#include "Level.h"
#include "Enemy.h"
#include "Animation.h"
#include "MainMenu.h"
#include <array>
#include <iostream>

const float winWidth = 1800.f;
const float winHeight = 1013.f;
bool testMenu = false;
bool Inventory = false;
float direction;

int main() {
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Game");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::Sprite grapplePoint, nullGrapplePoint;
    MainMenu menu;
    Level level;
    level.setBackground("assets/lvl1.png");
    level.setMusic("assets/assets_intro.ogg");
    Player dwarf(355.f, 800.f, 100.f, 80.f, "dwarves.png");
    Enemy enemy(2000, 2880, 48, 64, "assets/monster.png", 48, 92);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::I) {
                menu.inventory = !menu.inventory;
                dwarf.setSFX("assets/sfx_pageTurn.wav");
            }

            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
                level.levelSwitch = true;
            }

            menu.mainMenuControls(window);
            dwarf.setShot(event, window);
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        window.clear();

        if (!menu.inventory) {

            if (menu.pageNum == 0) {
                menu.setMainMenu(window);
            }

            else if (menu.pageNum == 3) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && menu.pageNum == 3)
                {
                    menu.pageNum = 0;
                }

                dwarf.checkDoor(level);

                if (!level.levelOneComplete && !level.levelTwoComplete && !level.levelThreeComplete) {
                    level.buildLevelOnePlatforms();
                }
                else if (level.levelOneComplete && !level.levelTwoComplete) {
                    level.buildLevelTwoPlatforms();
                }
                else if (level.levelOneComplete && level.levelTwoComplete) {
                    level.buildLevelThreePlatforms(enemy);
                }

                
                window.draw(level.background);

                dwarf.setVelX();

                level.draw(window, dwarf);

                dwarf.initiateGrapple(level.grapplePoints, level.platforms, grapplePoint, window);

                //std::cout << grapplePoint.getPosition().y << std::endl;

                /*enemy.moveEnemyX(100.f, winWidth - 100.f);
                enemy.enemyCollision(dwarf);
                enemy.update(window);*/

                //dwarf.shoot(level.platforms, window);
                dwarf.checkBounds(level.platforms);
                dwarf.update(level.platforms, level.deathZone, window);
                window.draw(dwarf.bullet);
                window.draw(dwarf.healthBar);

                if (dwarf.cangrapple) {
                    dwarf.grapple(grapplePoint, nullGrapplePoint);
                }

                if (dwarf.rect.getGlobalBounds().intersects(level.lever.getGlobalBounds())) {
                    level.leverPulled = true;
                }

                if (dwarf.grappletopoint) {
                    dwarf.setRope(grapplePoint);
                    dwarf.drawRope(window);
                }

                ImGui::Begin("CheatMenu");

                if (ImGui::Button("Reset Position")) {
                    dwarf.setPosition(200, 860);
                }

                ImGui::End;
                ImGui::SFML::Render(window);

                menu.triggerGameOver(dwarf, level);
                menu.triggerGameFinished(level);

                //std::cout << level.levelOneComplete << " "<< pageNum << " " << level.levelTwoComplete << std::endl;

                sf::Vector2i position = sf::Mouse::getPosition(window);
                sf::Vector2f tracker = window.mapPixelToCoords(position);

                std::cout << tracker.x << " " << tracker.y << std::endl;
                window.display();
            }

            else if (menu.pageNum == 1) {
                menu.setControlsMenu(window);
            }

            else if (menu.pageNum == 4) {
                menu.setGameOverScreen(window, dwarf, level);
            }

            else if (menu.pageNum == 5) {
                menu.setVictoryScreen(window, enemy, dwarf, level);
            }
        }

        if (menu.inventory) {
            window.clear();

            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f tracker = window.mapPixelToCoords(position);
            menu.setInventoryMenu(window);
            menu.changeEquipment(dwarf, tracker);

            window.display();
        }
    }
    ImGui::SFML::Shutdown();
}