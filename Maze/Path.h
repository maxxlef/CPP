#include "vibes.h"     // Inclusion de la bibliothèque vibes pour le dessin graphique.
#include "Cell.h"      // Inclusion de la définition de la classe Cell.
#include "Maze.h"      // Inclusion de la définition de la structure Maze.
#include <iostream>    // Inclusion de la bibliothèque standard d'entrées/sorties (utilisé ici indirectement).
#include <algorithm>   // Inclusion de la bibliothèque algorithmique pour utiliser std::min et std::max.


class Path {

    public:

        Path(const Cell *c);
        ~Path();
        void add_to_path(const Cell *c);
        void display_link(const Cell *n1, const Cell *n2);
        void display_path();
        
        

    protected:

        const Cell *_c;
        Path *_next = nullptr;
        Path *_head = nullptr;
};