#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Font font;
    sf::Text menu[3];
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture introTexture;  // Nueva textura para la pantalla de introducci�n
    sf::Sprite introSprite;    // Sprite para la pantalla de introducci�n
    sf::Texture hudTexture;   // Nueva textura para la imagen HUD
    sf::Sprite hudSprite;     // Nuevo sprite para la imagen HUD
    int selectedItemIndex;
    bool showIntroScreen;      // Controla si se muestra la pantalla de introducci�n
    sf::Clock introClock;      // Temporizador para la pantalla de introducci�n

public:
    Menu(int width, int height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getPressedItem();
    bool isIntroComplete();  // Verifica si se ha completado el tiempo de la pantalla de introducci�n
    void resetIntro();       // Reinicia el estado de la pantalla de introducci�n
};

#endif // MENU_H

