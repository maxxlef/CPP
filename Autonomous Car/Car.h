#include "Road.h"  // Inclure la classe Road

#ifndef CAR_H
#define CAR_H


class Car {
    protected:
        const Road *_road;  // Pointeur constant vers un objet de la classe Road, en lecture seule
        float _x;           // Position de la voiture sur le cercle
        float _v = 0.;      // Vitesse de la voiture, nulle par défaut
        const Car *_frontCar; // Pointeur vers la voiture de devant (si elle existe)
        float _u = 1.0;  // Commande de contrôle

    public:
        Car();  // Constructeur par défaut
        // Constructeur prenant en paramètre un pointeur vers un objet de la classe Road et la position initiale
        Car(const Road *roadPtr, float initialPosition = 0.0);

        // Destructeur
        virtual~Car();

        // Accesseurs pour les variables de classe
        float getPosition() const;  // Renvoie la position x de la voiture
        float getSpeed() const;     // Renvoie la vitesse v de la voiture
        
        // Méthode pour définir la position et la vitesse de la voiture
        void setSpeed(float x, float speed);

        // Méthode pour arrêter la voiture
        void stop();

        // Méthode pour définir la voiture de devant
        void setFrontCar(const Car *carInFront);

        // Méthode pour récupérer la voiture de devant
        const Car *frontCar() const;

        // Méthode pour dessiner la voiture
        void draw() const;

        // Méthode pour calculer la fonction d'évolution du système
        void f(float u, float& xdot, float& vdot) const;

        // Méthode pour calculer la fonction de contrôle
        float u(float d0, float v0);

        // Méthode euler
        void euler(float u, float& x, float& v);

};

#endif // CAR_H
