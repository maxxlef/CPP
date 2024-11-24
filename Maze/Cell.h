
#ifndef CELL_H
#define CELL_H
#include <iostream>


class Cell {

    public:

        int _x, _y;               // Coordonnées de la cellule
        int _nb_neighb = 0;       // Nombre de voisins
        Cell** _neighb = nullptr; // Tableau de pointeurs vers les cellules voisines
        bool _displayed = false;  // Indique si la cellule a déjà été affichée
        bool _in_path = false;    // Indique si la cellule fait partie du chemin
        bool _written = false;    // Indique si la cellule a déjà été écrite
        
        Cell();  // Constructeur par défaut
        // Constructeur prenant en paramètre un pointeur vers un objet de la classe Road et la position initiale
        Cell(int x, int y);

        // Destructeur
        virtual~Cell();

        // Méthode pour ajouter un voisin
        void add_neighb(Cell *c);
        
        // Méthode pour ajouter deux voisins
        void add_neighb(Cell* c1, Cell* c2);

        // Méthode pour ajouter trois voisins
        void add_neighb(Cell* c1, Cell* c2, Cell* c3);

        // Méthode pour ajouter quatres voisins
        void add_neighb(Cell* c1, Cell* c2, Cell* c3, Cell* c4);

        // Méthode pour print une cellule
        void print() const;

        friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

        // Opérateur >> pour la désérialisation
        friend std::istream& operator>>(std::istream& is, Cell& cell);
};

#endif // CELL_H
