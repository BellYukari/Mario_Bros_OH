#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Mario.h"
#include <vector>

// Clase Mushroom que representa un hongo en el juego
class Mushroom {
public:
	sf::Sprite Mushroom_sprite; // Sprite del hongo
	Mushroom(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position); // Constructor que inicializa el sprite y la posición del hongo
	void Logic(Mario& mario); // Lógica de interacción del hongo con Mario
	void Collision(std::vector<sf::Sprite>& tiles, sf::Vector2f vel); // Verificación de colisiones con los tiles

	void update(float deltaTime, std::vector<sf::Sprite> tiles); // Actualización del hongo en función del tiempo y las colisiones

	bool activated = false; // Indica si el hongo ha sido activado
	bool done = false; // Indica si el hongo ha completado su lógica
	bool free = false; // Indica si el hongo está libre
	sf::Vector2f velocity; // Velocidad del hongo

private:
	sf::Clock frameCounter; // Reloj para contar el tiempo de cuadros
	int counter = 0; // Contador auxiliar
	sf::Vector2f position; // Posición del hongo
	sf::RectangleShape hitbox; // Caja de colisión del hongo
	bool right_collide = false; // Colisión derecha
	bool left_collide = false; // Colisión izquierda
	bool collide = true; // Estado de colisión
	int initial = 0; // Estado inicial del hongo
};

// Clase Enemy que representa un enemigo en el juego
class Enemy {
public:
	sf::Sprite Enemy_sprite; // Sprite del enemigo
	Enemy(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, std::string type); // Constructor que inicializa el enemigo
	void Collision(std::vector<sf::Sprite>& tiles, sf::Vector2f vel, std::vector<Enemy>& Enemy_v); // Colisiones del enemigo con otros objetos
	void Logic(Mario& mario); // Lógica de interacción del enemigo con Mario
	void update(float deltaTime, std::vector<sf::Sprite> tiles, std::vector<Enemy>& Enemy_v); // Actualización en función del tiempo y colisiones
	bool dead = false; // Estado del enemigo (si está muerto)
	int type = 0; // Tipo de enemigo
	bool done = false; // Estado de finalización de lógica
	bool canDestroy; // Si puede ser destruido

private:
	sf::Clock frameCounter; // Reloj de cuadros
	int counter = 0; // Contador auxiliar
	sf::Vector2f velocity; // Velocidad del enemigo
	sf::Vector2f position; // Posición del enemigo
	sf::RectangleShape hitbox; // Caja de colisión del enemigo
	bool right_collide = false; // Colisión derecha
	bool left_collide = false; // Colisión izquierda
	bool collide = true; // Estado de colisión
	bool dmg = true; // Estado de daño
	int initial = 0; // Estado inicial del enemigo
	int xFrame = 0; // Cuadro de animación en x
	std::string category; // Categoría del enemigo
	bool can = false; // Indicador adicional
	int coll = 0; // Contador de colisiones
};

// Clase Block que representa bloques en el juego
class Block {
public:
	sf::Sprite block_sprite; // Sprite del bloque

	bool hit = false; // Indica si el bloque ha sido golpeado
	bool active = false; // Si el bloque está activo
	bool broken = false; // Si el bloque está roto
	Block(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, int type); // Constructor del bloque
	void Collision(Mario& mario, std::vector<Mushroom>& Mushroom_v, std::vector<Enemy>& Enemy_v); // Colisiones del bloque

private:
	sf::Clock frameCounter; // Reloj de cuadros
	int counter = 0; // Contador auxiliar
};

// Clase Background que representa el fondo del juego
class Background {
public:
	sf::Sprite Background_sprite; // Sprite del fondo
	Background(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position); // Constructor que inicializa el fondo
};

// Clase Finish que representa el punto final en el juego
class Finish {
public:
	sf::Sprite Finish_sprite; // Sprite del punto final
	Finish(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, int type); // Constructor del punto final
	void Collision(Mario& mario); // Verificación de colisión con Mario
	int kind = 0; // Tipo de punto final
	int stage = 0; // Estado o etapa del punto final
	sf::Vector2f velocity; // Velocidad (si es aplicable)
};

// Clase Broken que representa bloques rotos en el juego
class Broken {
public:
	sf::Sprite block_sprite1, block_sprite2, block_sprite3, block_sprite4, block_sprite5; // Fragmentos del bloque roto

	Broken(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position); // Constructor que inicializa los fragmentos
	void Collision(Mario& mario); // Verificación de colisión con Mario

	bool activated = false; // Indica si el bloque ha sido activado
	bool done = false; // Estado de finalización de lógica

private:
	sf::Clock frameCounter; // Reloj de cuadros
	int counter = 0; // Contador auxiliar
};

// Clase CoinBlock que representa bloques de monedas en el juego
class CoinBlock {
public:
	sf::Sprite Coinblock_sprite; // Sprite del bloque de moneda
	sf::Sprite Coin_sprite; // Sprite de la moneda
	sf::Sprite Mushroom_sprite; // Sprite de hongo si aplica
	bool hit = false; // Indica si el bloque ha sido golpeado
	bool activated = false; // Estado de activación del bloque
	CoinBlock(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, int type); // Constructor
	void Collision(Mario& mario, std::vector<Mushroom>& Mushroom_v, std::vector<Enemy>& Enemy_v); // Colisiones con Mario

	sf::Clock frameCounter; // Reloj de cuadros
	float xFrame = 0.0f; // Cuadro de animación en x
	float wait = 0.15f; // Tiempo de espera entre cuadros
	int counter = 0; // Contador auxiliar
	int coin_counter = 0; // Contador de monedas
	int type = 0; // Tipo de bloque de moneda
};

// Clase Entity que agrupa todas las entidades del juego
class Entity
{
public:
	std::vector<Block> Block_v; // Vector de bloques
	std::vector<CoinBlock> CoinBlock_v; // Vector de bloques de monedas
	std::vector<Mushroom> Mushroom_v; // Vector de hongos
	std::vector<Broken> Broken_v; // Vector de bloques rotos
	std::vector<Background> Background_v; // Vector de fondos
	std::vector<Enemy> Enemy_v; // Vector de enemigos
	std::vector<Finish> Finish_v; // Vector de puntos finales
	std::vector<sf::Sprite> Sprite_v; // Vector de sprites genéricos

	bool finish = false; // Indica si se ha llegado al final
	bool done = false; // Indica si la lógica de entidades ha concluido

	void createBlock(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, int type); // Crear bloque
	void createCoinBlock(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, int type); // Crear bloque de moneda
	void createMushroom(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect); // Crear hongo
	void createBroken(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect); // Crear bloque roto
	void createBackground(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect); // Crear fondo
	void createFinish(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, int type); // Crear punto final
	void createEnemy(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, std::string type); // Crear enemigo

	void destroyBlock(sf::Vector2f pos); // Destruir bloque
	void destroyMushroom(sf::Vector2f pos); // Destruir hongo
	void destroyBroken(sf::Vector2f pos); // Destruir bloque roto
	void destroyEnemy(sf::Vector2f pos); // Destruir enemigo

	void DrawToScreen(sf::RenderWindow& window, Mario& mario, float deltaTime, std::vector<sf::Sprite> tiles); // Dibujar entidades en la pantalla
	void LoadFromFile(std::string FileName, sf::Color backgroundColor, Mario& mario, Entity& EntityList, sf::Texture& tileset, sf::Texture& enemyset); // Cargar configuración desde archivo
};


