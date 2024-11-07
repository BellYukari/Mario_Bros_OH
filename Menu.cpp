#include "Menu.h"
#include <iostream>

Menu::Menu(int width, int height) : showIntroScreen(false) {
    // Cargar la textura de fondo del menú
    if (!backgroundTexture.loadFromFile("img/menu.png")) {
        std::cerr << "Error al cargar la textura del fondo del menú." << std::endl;
    }
    background.setTexture(backgroundTexture);

    // Cargar la imagen de la pantalla de introducción
    if (!introTexture.loadFromFile("img/0.png")) {  // Usa la imagen que prefieras
        std::cerr << "Error al cargar la textura de la pantalla de introducción." << std::endl;
    }
    introSprite.setTexture(introTexture);
    introSprite.setPosition(width / 2 - introSprite.getGlobalBounds().width / 2,
        height / 2 - introSprite.getGlobalBounds().height / 2);

    // Cargar la imagen HUD en lugar del título de texto
    if (!hudTexture.loadFromFile("img/HUD.png")) {
        std::cerr << "Error al cargar la textura HUD." << std::endl;
    }
    hudSprite.setTexture(hudTexture);
    hudSprite.setPosition(width / 3 - hudSprite.getGlobalBounds().width / 3, height / 6);
    float scaleX = 2.5f;  // Aumentar la escala en el eje X (puedes aumentar este valor)
    float scaleY = 3.5f;  // Aumentar la escala en el eje Y (puedes aumentar este valor)
    hudSprite.setScale(scaleX, scaleY);

    // Configuración del menú
    if (!font.loadFromFile("Fonts/font.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }
    std::string menuOptions[3] = { "Iniciar", "Opciones", "Salir" };
    for (int i = 0; i < 3; i++) {
        menu[i].setFont(font);
        menu[i].setString(menuOptions[i]);
        menu[i].setCharacterSize(40);
        menu[i].setFillColor(sf::Color::White);
        menu[i].setPosition(width / 2 - menu[i].getGlobalBounds().width / 2, height / 2 + (i * 60));
    }

    selectedItemIndex = 0;
    menu[selectedItemIndex].setFillColor(sf::Color::Red);
}

void Menu::draw(sf::RenderWindow& window) {
    if (showIntroScreen) {
        window.draw(introSprite);
    }
    else {
        window.draw(background);
        window.draw(hudSprite);  // Dibujar la imagen HUD en lugar del título
        for (int i = 0; i < 3; i++) {
            window.draw(menu[i]);
        }
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < 3) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getPressedItem() {
    return selectedItemIndex;
}

bool Menu::isIntroComplete() {
    return showIntroScreen && introClock.getElapsedTime().asSeconds() >= 3;
}

void Menu::resetIntro() {
    showIntroScreen = true;
    introClock.restart();
}

