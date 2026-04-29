#include "Spaceship.h"
#include "Constants.h"
#include "Exceptions.h"
#include <iostream>

// Constructor
Spaceship::Spaceship() : Entity(0.f, 0.f), image(), sprite(image) {

    if (!image.loadFromFile("Graphics/spaceship.png")) {
        throw ResourceException("Graphics/spaceship.png"); 
    }

    sprite.setTexture(image, true);

    //centram nava pe orizontală și o plasam în partea de jos a ecranului
    position.x = (static_cast<float>(Config::SCREEN_WIDTH) - image.getSize().x) / 2.f;
    position.y = static_cast<float>(Config::SCREEN_HEIGHT) - image.getSize().y - 20.f;
    sprite.setPosition(position);
}

// Constructor de copiere
Spaceship::Spaceship(const Spaceship& other) : Entity(other), image(other.image), sprite(image) {
    sprite.setTexture(image, true);
    sprite.setPosition(position);
}

// Funcția swap
void swap(Spaceship& first, Spaceship& second) noexcept {
    using std::swap;
    swap(first.position, second.position);
    swap(first.image, second.image);
    first.sprite.setTexture(first.image, true);
    second.sprite.setTexture(second.image, true);
}

//operator de atribuire folosind copy-and-swap
Spaceship& Spaceship::operator=(Spaceship other) {
    swap(*this, other);
    return *this;
}


void Spaceship::doDraw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Spaceship::doUpdate() {
    // Sincronizăm sprite-ul cu poziția logică
    sprite.setPosition(position);
}

void Spaceship::MoveLeft() {
    position.x -= 7; //mutam nava la stanga cu 7 pixeli
    if (position.x < 0) {  //daca depasim marginea 
        position.x = 0;
    }
}

void Spaceship::MoveRight() {
    position.x += 7;
    float limitaDreapta = static_cast<float>(Config::SCREEN_WIDTH) - image.getSize().x;
    if (position.x >= limitaDreapta) {
        position.x = limitaDreapta;
    }
}   


std::shared_ptr<Spaceship> Spaceship::clone() const {
    return std::make_shared<Spaceship>(*this); //returnează o copie într-un Smart Pointer
}
void Spaceship::fire() {
    if (fireClock.getElapsedTime().asSeconds() > fireInterval) {
        //poziționăm laserul în vârful navei
        sf::Vector2f laserPos = { position.x + image.getSize().x / 2.f - 2.f, position.y };
        lasers.push_back(std::make_shared<Laser>(laserPos, -10.f)); //adaugam laserul in vector, il facem sa se miste in sus
        //dacă avem clonă, trage și ea
        if (cloneActive && shipClone) {
            lasers.push_back(std::make_shared<Laser>(sf::Vector2f(shipClone->position.x + 20, shipClone->position.y), -10.f));
        }
        fireClock.restart(); //resetează cronometrul pentru următorul foc
    }
}
void Spaceship::activateSpeedBoost() {
    speedBoostActive = true;
    fireInterval = 0.15f; //trage mult mai rapid
    powerUpClock.restart();
}

void Spaceship::activateClone() {
    cloneActive = true;
    // Cream o copie a navei curente
    auto duplicated = this->clone();
    shipClone = std::dynamic_pointer_cast<Spaceship>(duplicated);
    powerUpClock.restart();
}

void Spaceship::updatePowerUps() {
    //daca a expirat timpul
    if ((speedBoostActive || cloneActive) && powerUpClock.getElapsedTime().asSeconds() > 5.0f) {
        speedBoostActive = false;
        cloneActive = false;
        fireInterval = 0.5f; //revine la viteza normală
        shipClone = nullptr; //stergem clona
    }

    if (cloneActive && shipClone) {
        //clona urmărește nava la o distanță fixă (50 pixeli la dreapta)
        shipClone->position = sf::Vector2f(position.x + 50.f, position.y);
        shipClone->doUpdate();
    }
}
void Spaceship::draw(sf::RenderWindow& window) {
    //apelăm metoda din Entity ca să desenăm nava de bază
    Entity::draw(window);

    //daca avem o clonă, o punem și pe ea să se deseneze
    if (shipClone != nullptr) {
        shipClone->draw(window);
    }
}