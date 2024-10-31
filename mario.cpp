#include "Mario.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

// Constructor de la clase Mario
Mario::Mario() {
    texture.loadFromFile("img/mariosheet.png"); // Carga la textura del sprite desde el archivo de imagen
    sprite.setTexture(texture); // Asigna la textura al sprite

    if (small) { // Si Mario está en su estado pequeño
        sprite.setTextureRect(sf::IntRect(29, 0, 17, 17)); // Define el área de textura para Mario pequeño
        sprite.setOrigin(sf::Vector2f(8.5, 8.5)); // Define el punto de origen para la rotación y escalado
    }

    if (!small) { // Si Mario está en su estado grande
        sprite.setTextureRect(sf::IntRect(29, 52, 17, 33)); // Define el área de textura para Mario grande
        sprite.setOrigin(sf::Vector2f(8.5, 16.5)); // Define el punto de origen para la rotación y escalado
    }

    sprite.setScale(sf::Vector2f(scale, scale)); // Escala el sprite de Mario
    sprite.setPosition(sf::Vector2f(100, 0)); // Coloca a Mario en la posición inicial

    vision.setSize(sf::Vector2f(1024, 968)); // Establece el tamaño de la visión de Mario
}

// Método que retorna la posición actual de Mario
sf::Vector2f Mario::getPosition()
{
    return sprite.getPosition();
}

// Verifica colisión con un tile a la derecha
bool Mario::rc(sf::Sprite tile)
{
    return velocity.x >= 0 && sprite.getPosition().x < tile.getGlobalBounds().left && sprite.getPosition().y > tile.getGlobalBounds().top && sprite.getPosition().y < tile.getGlobalBounds().top + tile.getGlobalBounds().height + 20;
}

// Verifica colisión con un tile a la izquierda
bool Mario::lc(sf::Sprite tile)
{
    return velocity.x <= 0 && sprite.getPosition().x > tile.getGlobalBounds().left + tile.getGlobalBounds().width && sprite.getPosition().y > tile.getGlobalBounds().top && sprite.getPosition().y < tile.getGlobalBounds().top + tile.getGlobalBounds().height + 20;
}

// Verifica si Mario está en la parte superior de un tile
bool Mario::onTop(sf::Sprite tile)
{
    return velocity.y > 0 && sprite.getPosition().y < tile.getGlobalBounds().top && sprite.getPosition().x > tile.getGlobalBounds().left - 20 && sprite.getPosition().x < tile.getGlobalBounds().left + tile.getGlobalBounds().width + 20;
}

// Verifica si Mario está debajo de un tile
bool Mario::beneath(sf::Sprite tile)
{
    return velocity.y < 0 && sprite.getPosition().y > tile.getGlobalBounds().top + tile.getGlobalBounds().height && sprite.getPosition().x > tile.getGlobalBounds().left - 20 && sprite.getPosition().x < tile.getGlobalBounds().left + tile.getGlobalBounds().width + 20;
}


// Control de la animación del sprite de Mario
void Mario::animate(std::string animation)
{
    if (animation == "idle") { // Animación de inactividad
        if (small) {
            sprite.setTextureRect(sf::IntRect(211, 0, 17, 17));
        }
        if (!small) {
            sprite.setTextureRect(sf::IntRect(209, 52, 17, 33));
        }
    }

    else if (animation == "running") { // Animación de correr
        if (small) {
            if (frameCounter.getElapsedTime().asSeconds() > 0.17f) {
                if (xFrame == 3) xFrame = 0;
                else xFrame++;
                frameCounter.restart();
            }
            sprite.setTextureRect(sf::IntRect(89 + (30 * xFrame), 0, 17, 17));
        }
        if (!small) {
            if (frameCounter.getElapsedTime().asSeconds() > 0.17f) {
                if (xFrame == 3) xFrame = 0;
                else xFrame++;
                frameCounter.restart();
            }
            sprite.setTextureRect(sf::IntRect(89 + (30 * xFrame), 52, 17, 33));
        }
    }

    else if (animation == "jumping") { // Animación de salto
        if (small) {
            sprite.setTextureRect(sf::IntRect(29, 0, 17, 17));
            if (key == "left") {
                sprite.setScale(sf::Vector2f(scale, scale));
            }
            if (key == "right") {
                sprite.setScale(sf::Vector2f(-scale, scale));
            }
        }
        if (!small) {
            sprite.setTextureRect(sf::IntRect(29, 52, 17, 33));
            if (key == "left") {
                sprite.setScale(sf::Vector2f(scale, scale));
            }
            if (key == "right") {
                sprite.setScale(sf::Vector2f(-scale, scale));
            }
        }
    }
    else if (animation == "mushroom") { // Animación de Mario al obtener un hongo
        sprite.setPosition(position);
        if (key == "right") {
            sprite.setScale(sf::Vector2f(scale, scale));
        }

        if (key == "left") {
            sprite.setScale(sf::Vector2f(-scale, scale));
        }
        if (frameCounter.getElapsedTime().asSeconds() > 0.1f) {  // Alterna el frame para el efecto de hongo
            xFrame = mushroom_count % 2;

            sprite.setTextureRect(sf::IntRect(211 - (2 * xFrame), 0 + (52 * xFrame), 17, 17 + (16 * xFrame)));
            sprite.setOrigin(8.5, 8.5 + (8 * xFrame));
            mushroom_count++;

            frameCounter.restart();
        }
        if (mushroom_count > 5) {  // Restablece el contador tras la animación del hongo
            pause = false;
            mushroom_count = 0;
            if (isJumping) {
                animate("jumping");
            }
        }
    }
    else if (animation == "hit") {  // Animación de golpe (por implementar)
        sprite.setPosition(position);

        if (key == "right") {
            sprite.setScale(sf::Vector2f(scale, scale));
        }

        if (key == "left") {
            sprite.setScale(sf::Vector2f(-scale, scale));
        }
        if (frameCounter.getElapsedTime().asSeconds() > 0.1f) {
            xFrame = hit_count % 2;

            sprite.setTextureRect(sf::IntRect(211 - (2 * xFrame), 0 + (52 * xFrame), 17, 17 + (16 * xFrame)));
            sprite.setOrigin(8.5, 8.5 + (8 * xFrame));
            hit_count++;

            frameCounter.restart();
        }
        if (hit_count > 6) {
            pause = false;
            hit_count = 0;
        }
    }
    else if (animation == "crouching") { // Animación de agacharse
        sprite.setTextureRect(sf::IntRect(388, 56, 17, 23));
    }
    if (animation == "finish") {  // Animación de finalización de nivel
        if (small) {
            velocity.x = 0;
            velocity.y = 0;
            sprite.setTextureRect(sf::IntRect(328, 29, 17, 17));
            sprite.setScale(scale, scale);
            if (finish_counter == 0) {
                sprite.setPosition(sprite.getPosition().x + 2, sprite.getPosition().y);
                finish_counter++;
            }
        }
        else {
            velocity.x = 0;
            velocity.y = 0;
            sprite.setTextureRect(sf::IntRect(389, 87, 17, 32));
            sprite.setScale(scale, scale);
            if (finish_counter == 0) {
                sprite.setPosition(sprite.getPosition().x + 2, sprite.getPosition().y);
                finish_counter++;
            }
        }
    }
}


// Maneja las colisiones de Mario con los tiles
void Mario::Collision(std::vector<sf::Sprite>& tiles) {
    a = false;
    left = false;
    right = false;

    hitbox.setPosition(sprite.getPosition());

    if (small || crouching) {  // Define el hitbox de Mario pequeño
        hitbox.setSize(sf::Vector2f(52, 52));
        hitbox.setOrigin(26, 26);

        for (int i = 0; i < tiles.size(); i++) { // Verifica colisiones con cada tile
            if (hitbox.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                if (rc(tiles[i])) { // Colisión derecha
                    velocity.x = 0;
                    right_collide = true;
                    right = true;
                }

                if (lc(tiles[i])) {  // Colisión izquierda
                    velocity.x = 0;
                    left_collide = true;
                    left = true;
                }

                if (onTop(tiles[i])) { // Colisión arriba
                    if (crouching) {
                        sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top - 23));
                    }
                    else {
                        sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top - 26));
                    }
                    velocity.y = 0;
                    isJumping = false;
                    collide = true;
                    a = true;
                }

                if (beneath(tiles[i])) { // Colisión abajo
                    sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top + tiles[i].getGlobalBounds().height + 26));
                    velocity.y = 10;
                }
            }
        }
    }
// Verifica si Mario no es pequeño y no está agachado
if (!small && !crouching) {
    // Configura el tamaño y origen del hitbox de Mario
    hitbox.setSize(sf::Vector2f(52, 104));
    hitbox.setOrigin(26, 52);

    // Recorre todos los tiles para verificar colisiones
    for (int i = 0; i < tiles.size(); i++) {
        // Comprueba si el hitbox de Mario intersecta con el tile actual
        if (hitbox.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
            // Si Mario choca desde la derecha del tile, detiene su movimiento hacia la derecha
            if (rc(tiles[i])) {
                velocity.x = 0;
                right_collide = true;
                right = true;
            }

            // Si Mario choca desde la izquierda del tile, detiene su movimiento hacia la izquierda
            if (lc(tiles[i])) {
                velocity.x = 0;
                left_collide = true;
                left = true;
            }

            // Si Mario está sobre el tile, ajusta su posición para que esté justo encima y detiene su caída
            if (onTop(tiles[i])) {
                sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top - 52));
                velocity.y = 0;
                isJumping = false; // Mario ya no está saltando
                collide = true;    // Marca colisión en el suelo
                a = true;          // Bandera auxiliar para colisión
            }

            // Si Mario está debajo del tile, ajusta su posición y lo empuja ligeramente hacia abajo
            if (beneath(tiles[i])) {
                sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top + tiles[i].getGlobalBounds().height + 52));
                velocity.y = 10;   // Empuja a Mario hacia abajo
            }
        }
    }
}

// Si no hubo colisión en el suelo, desactiva la bandera de colisión
if (!a) {
    collide = false;
}
// Si no hubo colisión hacia la izquierda, desactiva la bandera de colisión izquierda
if (!left) {
    left_collide = false;
}
// Si no hubo colisión hacia la derecha, desactiva la bandera de colisión derecha
if (!right) {
    right_collide = false;
}

}

// Actualiza la lógica de Mario en cada frame
void Mario::update(float deltaTime, std::vector<sf::Sprite> tiles)
{
    if (finish) { // Si Mario ha terminado el nivel
        if (stage == 0) { // Primer etapa después de terminar
            velocity.y = 300.0f; // Mario se mueve hacia abajo
        }
        sprite.move(velocity * deltaTime); // Mueve el sprite de Mario
        Collision(tiles); // Verifica colisiones
        if (collide && stage == 0) { // Si hay colisión en la primera etapa
            stage = 1;
            finish_counter = 0;
        }
        if (stage == 1) { // Segunda etapa
            sprite.setScale(-scale, scale); // Invierte la escala horizontal
            if (finish_counter < 4) {
                sprite.setPosition(sprite.getPosition().x + 16, sprite.getPosition().y); // Desplaza sprite
                finish_counter++;
            }
            if (finish_counter == 4) {
                stage = 2;
            }
        }
        if (stage == 3) { // Etapa de carrera final
            animate("running"); // Anima a Mario corriendo
            velocity.x = 150.0f; // Velocidad de avance
            velocity.y += 1500.0f; // Aplica gravedad
            if (getPosition().x > 13094) { // Si llega al límite
                velocity.x = 0;
                stage = 4;
            }
        }
        if (stage == 4) { // Etapa de espera
            animate("idle"); // Mario en espera
            sprite.setScale(scale, scale); // Restaura escala
            velocity.y = 0; // Detiene movimiento vertical
        }
    }

    if (dead) { // Lógica cuando Mario está muerto
        sprite.setTextureRect(sf::IntRect(389, 15, 17, 17)); // Cambia la textura a la de "muerte"
        if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter <= 40) {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 3); // Mario asciende
            counter++;
            frameCounter.restart();
        }
        if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter > 40 && counter <= 200) {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 4); // Mario desciende
            counter++;
            frameCounter.restart();
        }
    }

    if (!dead) // Lógica cuando Mario no está muerto
    {
        if (!pause) // Si el juego no está en pausa
        {
            if (velocity.x != 0 && !crouching) { // Reduce velocidad de Mario en el suelo
                if (velocity.x > 0) {
                    velocity.x -= 2.0f; // Disminuye velocidad positiva
                    if (velocity.x < 0) {
                        velocity.x = 0;
                    }
                }
                if (velocity.x < 0) {
                    velocity.x += 2.0f; // Aumenta velocidad negativa
                    if (velocity.x > 0) {
                        velocity.x = 0;
                    }
                }
            }

            velocity.y += 1500.0 * deltaTime; // Aplica gravedad

            position = sprite.getPosition(); // Actualiza posición

            if (position.y > 1000) { // Si cae fuera de los límites
                dead = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isJumping && !small) { // Agachado
                animate("crouching");
                crouching = true;

                if (crouch < 4) { // Ajusta la posición de Mario al agacharse
                    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 7);
                    crouch++;
                }

                if (key == "right") {
                    sprite.setScale(sf::Vector2f(scale, scale)); // Orienta derecha
                }

                if (key == "left") {
                    sprite.setScale(sf::Vector2f(-scale, scale)); // Orienta izquierda
                }
            }

            if (crouching) { // Si Mario está agachado
                if (velocity.x != 0) {
                    if (velocity.x > 0) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            velocity.x -= 0.5f; // Reduce velocidad al agacharse
                        }
                        else {
                            velocity.x -= 1.0f;
                        }
                    }
                    if (velocity.x < 0) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            velocity.x += 0.5f;
                        }
                        else {
                            velocity.x += 1.0f;
                        }
                    }
                }
            }

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // Termina de agacharse
                crouching = false;
                crouch = 0;
                if (isJumping) {
                    animate("jumping"); // Cambia animación si está saltando
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !crouching) // Movimiento a la derecha
            {
                if (!isJumping && !right_collide) {
                    animate("running"); // Anima corriendo
                    sprite.setScale(sf::Vector2f(-scale, scale));
                    key = "right";
                }
                if (!right_collide) { // Aumenta velocidad
                    if (velocity.x < 500.0f) {
                        velocity.x += 2.40f;
                    }
                    else {
                        velocity.x = 500.0f; // Limita velocidad máxima
                    }
                }
            }

            else if (position.x >= 17 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !crouching) // Movimiento a la izquierda
            {
                if (!isJumping && !left_collide) {
                    animate("running");
                    sprite.setScale(sf::Vector2f(scale, scale));
                    key = "left";
                }
                if (!left_collide) {
                    if (velocity.x > -500.0f) {
                        velocity.x -= 2.40f;
                    }
                    else {
                        velocity.x = -500.0f;
                    }
                }
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !crouching && !isJumping) {
                animate("idle"); // Cambia a animación inactiva

                if (key == "right") {
                    sprite.setScale(sf::Vector2f(scale, scale));
                }
                if (key == "left") {
                    sprite.setScale(sf::Vector2f(-scale, scale));
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) // Salto
            {
                if (!crouching) {
                    animate("jumping");
                }
                isJumping = true;
                velocity.y = -880.0f; // Velocidad de salto
            }

            if (collide && !crouching) // Si colisiona en suelo
            {
                isJumping = false; // Finaliza salto

                if (velocity.x == 0) {
                    animate("idle");

                    if (key == "right") {
                        sprite.setScale(sf::Vector2f(scale, scale));
                    }
                    if (key == "left") {
                        sprite.setScale(sf::Vector2f(-scale, scale));
                    }
                }
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) velocity.y = 0;
            }
            sprite.move(velocity * deltaTime); // Mueve sprite basado en velocidad y tiempo
            Collision(tiles); // Verifica colisiones
        }

        if (pause) { // Si está en pausa, muestra animación correspondiente
            if (activation == "mushroom") {
                animate("mushroom");
            }

            if (activation == "hit") {
                animate("hit");
            }
            if (activation == "finish") {
                if (stage == 0) {
                    animate("finish");
                }
                finish = true;
            }
        }
    }
}
