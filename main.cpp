#include <iostream>
#include "Mario.h" // Incluir la clase Mario para controlar al personaje principal
#include "text.h"  // Incluir la clase Tile para manejar los bloques y el entorno del juego
#include <vector>
#include <SFML/Graphics.hpp> // Librer�a SFML para gr�ficos y ventanas

int main() {
    sf::Clock Clock; // Reloj para medir el tiempo transcurrido en cada frame

    int windowWidth = 1024; // Ancho de la ventana de juego
    int windowHeight = 896; // Altura de la ventana de juego
    bool restart = false; // Bandera para reiniciar el juego

    // Crear la ventana de juego con el tama�o especificado y el t�tulo
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Super Mario World");

    Mario mario; // Instanciar el objeto Mario para controlar al personaje
    Entity entity; // Instanciar la entidad que contendr� elementos del juego (como enemigos y bloques)

    // Cargar las texturas de los gr�ficos del juego (tiles y enemigos)
    sf::Texture texture;
    texture.loadFromFile("img/Tilesheet.png"); // Textura de los bloques y fondo

    sf::Texture enemyset;
    enemyset.loadFromFile("img/enemies_sprites.png"); // Textura de los enemigos

    // Cargar el nivel desde un archivo, configurando las entidades, texturas y colores de fondo
    entity.LoadFromFile("nivel/1-1.wd", sf::Color(26, 128, 182, 255), mario, entity, texture, enemyset);

    // Configurar la vista inicial de la c�mara, centrada en la ventana
    sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
    unsigned view_x = 0; // Variable para el desplazamiento horizontal de la vista

    // Bucle principal del juego
    while (window.isOpen())
    {
        sf::Event Event; // Evento para manejar interacciones como cerrar la ventana
        float deltaTime = Clock.restart().asSeconds(); // Tiempo transcurrido desde el �ltimo frame

        // Bucle de eventos para verificar eventos dentro de la ventana
        while (window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed) // Si se cierra la ventana
                window.close();
        }

        // Ajustar la vista seg�n la posici�n de Mario para desplazar la c�mara
        if (mario.getPosition().x >= windowWidth / 2)
        {
            view_x = mario.getPosition().x - windowWidth / 2;
        }
        view.reset(sf::FloatRect(view_x, 0, windowWidth, windowHeight)); // Actualizar la vista
        mario.vision.setPosition(view_x, 0); // Actualizar la posici�n de la "visi�n" de Mario

        // Reiniciar el juego si se presiona Enter
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            restart = true;
        }

        // Configurar la vista en la ventana y actualizar el estado de Mario
        window.setView(view);
        mario.update(deltaTime, entity.Sprite_v);

        // Limpiar la pantalla con el color de fondo
        window.clear(sf::Color(26, 128, 182, 255));

        // Dibujar entidades y elementos del juego en la pantalla
        entity.DrawToScreen(window, mario, deltaTime, entity.Sprite_v);

        // Mostrar los elementos dibujados en pantalla
        window.display();
    }
}
