#include "Road.h"
#include "Car.h"
#include "AutonomousCar.h"

// Constructeur paramétré
Road::Road(float l, const std::string& figureName) : _l(l), _figureName(figureName)
{
    vibes::beginDrawing();
    vibes::newFigure(figureName);
    vibes::setFigureProperties(figureName, 
                               vibesParams("x", 100, "y", 100,
                                           "width", 400, "height", 400));
    vibes::axisLimits(-20., 20., -20., 20.);
}

// Destructeur
Road::~Road() = default;


// Accesseur pour la longueur de la route
float Road::length() const {
    return _l;
}

// Accesseur pour le rayon de la route
float Road::radius() const {
    return _l / (2 * M_PI);
}

// Accesseur pour le nom de la figure
std::string Road::figureName() const {
    return _figureName;
}

// Mutateur pour la longueur de la route
void Road::setLength(float l) {
    _l = l;
}
// Méthode pour dessiner la route
void Road::draw(const std::vector<Car>& cars) const {
    // Dessiner la route
    vibes::clearFigure(_figureName);
    vibes::drawCircle(0, 0, radius() + 2.5, "black[gray]");
    vibes::drawCircle(0, 0, radius() - 2.5, "black[white]");

    // Dessiner les voitures
    for (const Car& car : cars) {
        car.draw();  // Appeler la méthode draw() de chaque voiture
    }

}

// Méthode pour dessiner la route
void Road::draw(const std::vector<AutonomousCar>& cars) const {
    // Dessiner la route
    vibes::clearFigure(_figureName);
    vibes::drawCircle(0, 0, radius() + 2.5, "black[gray]");
    vibes::drawCircle(0, 0, radius() - 2.5, "black[white]");

    // Dessiner les voitures
    for (const Car& car : cars) {
        car.draw();  // Appeler la méthode draw() de chaque voiture
    }

}

float Road::sawtooth(float x) const {
    // value between 0 and l (road length)
    return x - _l * floor(x / _l);
}
 

float Road::circular_dist(const Car& car1, const Car& car2) const
{
    float x1 = car1.getPosition();
    float x2 = car2.getPosition();
    return sawtooth(x2 - x1);
}

bool Road::collision(const Car& car1, const Car& car2) const
{
    return circular_dist(car1, car2) < 4.0;
}