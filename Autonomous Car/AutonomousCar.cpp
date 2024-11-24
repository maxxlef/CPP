#include "AutonomousCar.h"
#include "Road.h"

// Constructeur paramétré
AutonomousCar::AutonomousCar(const Road *roadPtr, float initialPosition, float d0, float v0) :
    Car(roadPtr, initialPosition), _d0(d0), _v0(v0) 
{

}

// Méthode pour calculer la fonction de contrôle
float AutonomousCar:: u()
{
    // Calculer la distance circulaire entre la voiture et celle de devant
    float d = _road -> circular_dist(*this, *_frontCar);

    // Calculer la vitesse relative
    float vi_1 = _frontCar -> getSpeed();

    // Calculer la commande de contrôle
    _u = (d - _d0) + (vi_1 - _v) + (_v0 - _v);
    return _u;
}