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

    // Posición de Mario en el espacio de juego
    sf::Vector2f position;

    // Caja de colisión de Mario
    sf::RectangleShape hitbox;

    // Temporizador para controlar las animaciones de los cuadros
    sf::Clock frameCounter;

    // Contador de los objetos que Mario recoge o los eventos que ocurren
    int mushroom_count = 0; // Contador de champiñones recogidos
    int hit_count = 0;      // Contador de impactos recibidos
    int finish_counter = 0;  // Contador para el estado de finalización

    // Escala para redimensionar el sprite de Mario
    float scale = 3.5f;

    // Variable para rastrear la posición del cuadro en la animación
    float xFrame = 0.0f;

    // Variables para manejar la dirección y estados de movimiento
    bool a = false;
    bool left = false;      // Si Mario se está moviendo a la izquierda
    bool right = false;     // Si Mario se está moviendo a la derecha

    // Variables de colisión
    bool collide = false;       // Colisión general
    bool right_collide = false; // Colisión en la derecha
    bool left_collide = false;  // Colisión en la izquierda

public:
    // Constructor de la clase Mario
    Mario();

    // Método para animar a Mario según el nombre de la animación
    void animate(std::string animation);

    // Método para actualizar el estado de Mario en cada cuadro de juego
    void update(float deltaTime, std::vector<sf::Sprite> tiles);

    // Métodos de colisión para cada lado de Mario
    bool rc(sf::Sprite tile);     // Verifica colisión a la derecha
    bool lc(sf::Sprite tile);     // Verifica colisión a la izquierda
    bool onTop(sf::Sprite tile);  // Verifica si Mario está sobre un tile
    bool beneath(sf::Sprite tile);// Verifica si Mario está debajo de un tile

    // Obtiene la posición actual de Mario
    sf::Vector2f getPosition();

    // Sprite de Mario para dibujarlo en pantalla
    sf::Sprite sprite;

    // Vector que representa la velocidad de Mario
    sf::Vector2f velocity;

    // Rectángulo que representa la "visión" de Mario para interacciones cercanas
    sf::RectangleShape vision;

    // Variable que almacena la tecla de entrada actual
    std::string key;

    // Contador de monedas recolectadas
    int coin = 0;

    // Estado de vida de Mario
    bool dead = false;

    // Estado de tamaño de Mario (si es pequeño o grande)
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

    // Estado de activación de alguna habilidad o condición especial
    std::string activation = "";

    // Estado de salto
    bool isJumping = true;

    // Método para gestionar las colisiones de Mario con el entorno
    void Collision(std::vector<sf::Sprite>& tiles);
};

