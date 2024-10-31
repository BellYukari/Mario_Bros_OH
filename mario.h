#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

// Clase Mario que representa el personaje principal en el juego
class Mario
{
private:
    // Textura para el personaje de Mario
    sf::Texture texture;

    // Posici�n de Mario en el espacio de juego
    sf::Vector2f position;

    // Caja de colisi�n de Mario
    sf::RectangleShape hitbox;

    // Temporizador para controlar las animaciones de los cuadros
    sf::Clock frameCounter;

    // Contador de los objetos que Mario recoge o los eventos que ocurren
    int mushroom_count = 0; // Contador de champi�ones recogidos
    int hit_count = 0;      // Contador de impactos recibidos
    int finish_counter = 0;  // Contador para el estado de finalizaci�n

    // Escala para redimensionar el sprite de Mario
    float scale = 3.5f;

    // Variable para rastrear la posici�n del cuadro en la animaci�n
    float xFrame = 0.0f;

    // Variables para manejar la direcci�n y estados de movimiento
    bool a = false;
    bool left = false;      // Si Mario se est� moviendo a la izquierda
    bool right = false;     // Si Mario se est� moviendo a la derecha

    // Variables de colisi�n
    bool collide = false;       // Colisi�n general
    bool right_collide = false; // Colisi�n en la derecha
    bool left_collide = false;  // Colisi�n en la izquierda

public:
    // Constructor de la clase Mario
    Mario();

    // M�todo para animar a Mario seg�n el nombre de la animaci�n
    void animate(std::string animation);

    // M�todo para actualizar el estado de Mario en cada cuadro de juego
    void update(float deltaTime, std::vector<sf::Sprite> tiles);

    // M�todos de colisi�n para cada lado de Mario
    bool rc(sf::Sprite tile);     // Verifica colisi�n a la derecha
    bool lc(sf::Sprite tile);     // Verifica colisi�n a la izquierda
    bool onTop(sf::Sprite tile);  // Verifica si Mario est� sobre un tile
    bool beneath(sf::Sprite tile);// Verifica si Mario est� debajo de un tile

    // Obtiene la posici�n actual de Mario
    sf::Vector2f getPosition();

    // Sprite de Mario para dibujarlo en pantalla
    sf::Sprite sprite;

    // Vector que representa la velocidad de Mario
    sf::Vector2f velocity;

    // Rect�ngulo que representa la "visi�n" de Mario para interacciones cercanas
    sf::RectangleShape vision;

    // Variable que almacena la tecla de entrada actual
    std::string key;

    // Contador de monedas recolectadas
    int coin = 0;

    // Estado de vida de Mario
    bool dead = false;

    // Estado de tama�o de Mario (si es peque�o o grande)
    bool small = true;

    // Variable para indicar si Mario ha terminado el nivel
    bool finish = false;

    // Nivel o etapa actual en la que se encuentra Mario
    int stage = 0;

    // Estado de pausa
    bool pause = false;

    // Indica si Mario puede ser golpeado (invulnerabilidad temporal)
    bool can_be_hit = true;

    // Estado de agachado
    bool crouching = false;

    // Contador de tiempo de agachado
    int crouch = 0;

    // Contador de frames o animaciones
    int counter = 0;

    // Estado de activaci�n de alguna habilidad o condici�n especial
    std::string activation = "";

    // Estado de salto
    bool isJumping = true;

    // M�todo para gestionar las colisiones de Mario con el entorno
    void Collision(std::vector<sf::Sprite>& tiles);
};

