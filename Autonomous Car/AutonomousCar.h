#ifndef _AutonomousCar_h
#define _AutonomousCar_h
#include "Car.h"
#include "Road.h"



#endif // _AutonomousCar_h

class AutonomousCar : public Car // Hérite de Car
{
    public:
        // Constructeur prenant en paramètre un pointeur vers un objet de la classe Road et la position initiale
        AutonomousCar(const Road *roadPtr, float initialPosition = 0.0, float d0 = 2.0, float v0 = 10.0);

        // Méthode pour calculer la fonction de contrôle
        float u();

    private:
        float _d0 = 4.0; // Distance de sécurité
        float _v0 = 0; // Vitesse de consigne
        float _u = 1;  // Commande de contrôle
};