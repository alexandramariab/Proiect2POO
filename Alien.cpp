//
// Created by Alexandra on 4/16/2026.
//
#include "Alien.h"
#include "Constants.h"
#include <iostream>
#include "Exceptions.h"

float Alien::speed = 2.0f;
int Alien::direction = 1;

Alien::Alien(float x, float y, int type) : Entity(x, y), type(type), alive(true), texture(), sprite(texture) {
    std::string path = "Graphics/alien_" + std::to_string(type) + ".png";
    if (!texture.loadFromFile(path)) {
        throw ResourceException(path);
    }
    sprite.setTexture(texture, true);
    sprite.setPosition(position);
}

void Alien::doUpdate() {
    position.x += speed * direction;
    sprite.setPosition(position);
}
void Alien::moveDown(float distance) {
    position.y += distance;
    sprite.setPosition(position);
}

void Alien::changeDirection() {
    direction *= -1; //inversam directia de mers
}

float Alien::getRightEdge() const {
    return position.x + texture.getSize().x;
}

float Alien::getLeftEdge() const {
    return position.x;
}

void Alien::doDraw(sf::RenderWindow& window) {
    if (alive) window.draw(sprite);
}

sf::Vector2f Alien::getCenter() const {
    return { position.x + texture.getSize().x / 2.f, position.y + texture.getSize().y };
}