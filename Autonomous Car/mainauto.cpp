#include "Road.h"
#include "Car.h"
#include "AutonomousCar.h"
#include <vector>
#include <unistd.h> // pour usleep
#include <iostream>
#include <cmath> // pour std::floor

int main() {
    // Initialiser les paramètres
    float t = 0.0;
    float t_end = 100.0;
    const float dt = 0.05;
    int n = 3;  // Nombre de voitures

    // Création des routes
    float roadLength = 100.0;  // Longueur de la route
    Road road2(roadLength, "Road2");

    // Création des vecteurs de voitures
    float d0 = roadLength / n;  // Distance de sécurité
    float v0 = 10.0;  // Vitesse de consigne
    std::vector<AutonomousCar> autocars;

    // Créer n voitures et les placer sur la route
    for (int i = 0; i < n; ++i) {
        autocars.push_back(AutonomousCar(&road2, 4.0 * i, d0, v0));  // Chaque voiture est placée à x = 4 * i
    }

    // Lier chaque voiture à la suivante
    for (int i = 0; i < n; ++i) {
        autocars[i].setFrontCar(&autocars[(i + 1) % n]);  // La dernière voiture est liée à la première
    }

    // Dessiner la route et les voitures
    road2.draw(autocars);

    float lastPrintTime = 0.0;  // Temps du dernier affichage d'informations

    while (t <= t_end) {
        usleep(dt * 500000.);  // Pause

        for (int i = 0; i < n; ++i) {
            // Calculer la fonction d'évolution du système pour chaque voiture autonome
            float position2 = autocars[i].getPosition();
            float speed2 = autocars[i].getSpeed();
            autocars[i].euler(autocars[i].u(), position2, speed2);

            // Afficher les informations toutes les secondes
            if (std::floor(t) > lastPrintTime) {  // Comparer les secondes entières
                std::cout << "Distance entre voiture autonome " << n - 1 << " et voiture " << 0 << " : " 
                          << road2.circular_dist(autocars[n - 1], autocars[0]) << std::endl;
                std::cout << "Position de la voiture autonome " << n - 1 << " : " 
                          << autocars[n - 1].getPosition() << std::endl;
                std::cout << "Position de la voiture " << 0 << " : " 
                          << autocars[0].getPosition() << std::endl;
                std::cout << "-------Temps : " << t << "---------" << std::endl;

                lastPrintTime = std::floor(t);  // Mettre à jour le temps du dernier affichage
            }

            // Détection de collision entre les voitures
            if (road2.collision(autocars[i], autocars[(i + 1) % n])) {
                autocars[i].stop();
            }
        }

        // Dessiner la route et les voitures
        road2.draw(autocars);

        // Incrémenter le temps
        t += dt;
    }

    return EXIT_SUCCESS;
}
