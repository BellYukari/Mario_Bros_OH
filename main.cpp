#include <iostream>
#include "Mario.h"      // Incluir la clase Mario para controlar al personaje principal
#include "text.h"       // Incluir la clase Tile para manejar los bloques y el entorno del juego
#include "Menu.h"       // Incluir la clase Menu para el men� principal
#include <vector>
#include <SFML/Graphics.hpp>

int main() {
    sf::Clock Clock; // Reloj para medir el tiempo transcurrido en cada frame

    int windowWidth = 1050;
    int windowHeight = 896;
    bool inGame = false;
    bool showIntro = true;  // Mostrar intro al principio

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Super Mario World");

    Mario mario;
    Entity entity;

    // Texturas para el juego
    sf::Texture texture;
    texture.loadFromFile("img/Tilesheet.png");

    sf::Texture enemyset;
    enemyset.loadFromFile("img/enemies_sprites.png");

    // Cargar el nivel desde un archivo
    entity.LoadFromFile("nivel/1-1.wd", sf::Color(26, 128, 182, 255), mario, entity, texture, enemyset);

    // Configurar la vista inicial de la c�mara
    sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
    unsigned view_x = 0;

    // Instanciar el men� principal
    Menu menu(windowWidth, windowHeight);

    while (window.isOpen()) {
        sf::Event Event;
        float deltaTime = Clock.restart().asSeconds();

        // Bucle de eventos
        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                window.close();

            // L�gica de navegaci�n del men�
            if (!inGame) {
                if (Event.type == sf::Event::KeyPressed) {
                    if (Event.key.code == sf::Keyboard::Up) menu.moveUp();
                    if (Event.key.code == sf::Keyboard::Down) menu.moveDown();
                    if (Event.key.code == sf::Keyboard::Enter) {
                        int selectedItem = menu.getPressedItem();
                        if (selectedItem == 0) {
                            showIntro = true;
                            menu.resetIntro();  // Reseteamos la intro cuando selecciona iniciar
                        }
                        else if (selectedItem == 2) {
                            window.close(); // Opci�n "Salir" seleccionada, cerrar ventana
                        }
                    }
                }
            }
        }

        if (showIntro) {
            if (menu.isIntroComplete()) {
                inGame = true;  // Empieza el juego
                showIntro = false;  // Termina la intro
            }
            else {
                window.clear();
                menu.draw(window);  // Dibuja la intro
                window.display();
                continue;
            }
        }

        if (inGame) {
            // L�gica y dibujo del juego
            if (mario.getPosition().x >= windowWidth / 2) {
                view_x = mario.getPosition().x - windowWidth / 2;
            }
            view.reset(sf::FloatRect(view_x, 0, windowWidth, windowHeight));
            mario.vision.setPosition(view_x, 0);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                inGame = false;
            }

            window.setView(view);
            mario.update(deltaTime, entity.Sprite_v);

            // Dibujar juego
            window.clear(sf::Color(135, 206, 235, 255));
            entity.DrawToScreen(window, mario, deltaTime, entity.Sprite_v);
        }
        else {
            // Dibujar el men�
            window.clear();
            menu.draw(window);
        }

        window.display();
    }

    return 0;
}
