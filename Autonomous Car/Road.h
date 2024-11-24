#include "vibes.h"
#include <cmath>
#include <vector>

#ifndef ROAD_H // Protection contre les inclusions multiples
#define ROAD_H
// Forward declaration de la classe Car
class Car;
class AutonomousCar;

class Road {
public:
    // Constructeur paramétré
    explicit Road(float l,const std::string& figureName);

    // Destructeur
    ~Road();

    // Accesseur : obtenir la circonférence de la route
    float length() const;

    // Accesseur : obtenir le rayon de la route
    float radius() const;

    // Accesseur : obtenir le nom de la figure
    std::string figureName() const;

    // Mutateur : définir la longueur de la route
    void setLength(float l);

    // Méthode pour dessiner la route
    void draw(const std::vector<Car>& cars) const;

    // Méthode pour dessiner la route
    void draw(const std::vector<AutonomousCar>& cars) const;

    // Méthode sawtooth
    float sawtooth(float x) const;

    // Méthode pour calculer la distance circulaire entre deux voitures
    float circular_dist(const Car& car1, const Car& car2) const;

    // Méthode pour détecter une collision entre deux voitures
    bool collision(const Car& car1, const Car& car2) const;


private:
    float _l; // Circonférence de la route
    std :: string _figureName;
};

#endif // ROAD_H