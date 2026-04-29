#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "Laser.h"
#include <vector>
#include <memory>

// Cerința 2.a: Moștenire
class Spaceship : public Entity {
private:
    sf::Texture image; 
    sf::Sprite sprite; // Obiectul grafic care permite desenarea și poziționarea imaginii
    std::vector<std::shared_ptr<Laser>> lasers; // Lista de proiectile trase de navă
    sf::Clock fireClock; // Cronometru intern pentru a preveni tragerea prea rapida

    void doUpdate() override;
    void doDraw(sf::RenderWindow& window) override;
    float fireInterval = 0.5f; //Timpul min dintre 2 focuri succesive
    bool speedBoostActive = false;
    bool cloneActive = false;
    sf::Clock powerUpClock; //Durata de viata a bonusurilor active
    std::shared_ptr<Spaceship> shipClone = nullptr; // Pointer către nava secundară creată de bonusul Clone

public:
    Spaceship(); //constructor
    ~Spaceship() override= default; //destructor
    Spaceship(const Spaceship& other); //constructor de copiere
    Spaceship& operator=(Spaceship other); //operator de atribuire 
    friend void swap(Spaceship& first, Spaceship& second) noexcept; //funcție de swap pentru copy-and-swap
   
    void MoveLeft();
    void MoveRight();

    void fire();
    std::vector<std::shared_ptr<Laser>>& getLasers() { return lasers; }

    std::shared_ptr<Spaceship> clone() const; //Creează o copie identică a navei
    sf::FloatRect getBounds() const override { return sprite.getGlobalBounds(); }
    void activateSpeedBoost();
    void activateClone();
    void updatePowerUps(); // Verifică dacă timpul bonusurilor a expirat
    void draw(sf::RenderWindow& window); // O suprascriem pentru a desena și clona

};

#endif//SPACESHIP_H