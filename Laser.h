#ifndef LASER_H
#define LASER_H

#include "Entity.h"

class Laser : public Entity {
private:
    float speed;
    bool active;
    sf::RectangleShape shape;

    void doUpdate() override;
    void doDraw(sf::RenderWindow& window) override;

public:
    Laser(sf::Vector2f pos, float speed);
    ~Laser() override = default;

    bool isActive() const { return active; }
    sf::FloatRect getBounds() const override { return shape.getGlobalBounds(); }


};

#endif//LASER_H