#include "Car.h"

Car::Car() : _road(nullptr), _x(0), _v(0) {}  // Initialisation par défaut


// Constructeur paramétré
Car::Car(const Road *roadPtr, float initialPosition) 
    : _road(roadPtr), _x(initialPosition), _v(0.0), _frontCar(nullptr) {
}

// Destructeur
Car::~Car() = default;

// Accesseur pour la position de la voiture
float Car::getPosition() const {
    return _x;
}

// Accesseur pour la vitesse de la voiture
float Car::getSpeed() const {
    return _v;
}

// Mutateur pour la position et la vitesse
void Car::setSpeed(float x, float v) {
    _x = x;
    _v = v;
}

// Méthode pour arrêter la voiture
void Car::stop() {
    setSpeed(_x, 0);
}

// Méthode pour définir l'adresse de la voiture de devant par pointeur en lecture
void Car::setFrontCar(const Car* carInFront) {
    _frontCar = carInFront;
}

// Méthode pour retourner l'adresse de la voiture de devant par pointeur en lecture
const Car* Car::frontCar() const {
    return _frontCar;
}

// Méthode pour dessiner la voiture
void Car::draw() const {
    // Calculer les coordonnées de la voiture sur le cercle
    float r = _road -> radius();
    float theta = _x / r;  // Angle en radians correspondant à la position sur le cercle
    float carX = r * cos(theta);
    float carY = r * sin(theta);

    // Dessiner la voiture (un tank) avec l'orientation correcte
    if (_road->circular_dist(*this, *_frontCar)<4.1)
    {
        vibes::drawTank(carX, carY, (theta + M_PI / 2.0) * (180.0 / M_PI), 4, "red[white]", vibesParams("figure", _road->figureName()));
    }
    else
    vibes::drawTank(carX, carY, (theta + M_PI / 2.0) * (180.0 / M_PI), 4, "black[white]", vibesParams("figure", _road->figureName()));
}

// Méthode pour calculer la fonction d'évolution du système
void Car:: f(float u, float& xdot, float& vdot) const
{
    // Calculer la dérivée de la position
    xdot = _v;

    // Calculer la dérivée de la vitesse
    vdot = u;
}

// Méthode euler
void Car:: euler(float u, float& _x, float& _v)
{
    float xdot, vdot;
    f(u, xdot, vdot);
    float dt = 0.05;
    setSpeed(_x + dt * xdot, _v + dt * vdot);
}