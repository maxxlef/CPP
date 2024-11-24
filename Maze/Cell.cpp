#include "Cell.h"

// Constructeur par défaut
Cell::Cell() : _x(0), _y(0), _nb_neighb(0), _written(false) {}

// Constructeur
Cell::Cell(int x, int y) : _x(x), _y(y) {}

// Destructeur pour libérer la mémoire
Cell::~Cell() {
    delete[] _neighb;
}

// Méthode pour ajouter un voisin
void Cell :: add_neighb(Cell* c) {
    // Vérifie si c est déjà un voisin
    for (int i = 0; i < _nb_neighb; i++) {
        if (_neighb[i] == c) {
            return; // c est déjà un voisin
        }
    }

    // Alloue dynamiquement un nouveau tableau de pointeurs de taille _nb_neighb + 1
    Cell** new_neighb = new Cell*[_nb_neighb + 1];
    
    // Copie les anciens voisins dans le nouveau tableau
    for (int i = 0; i < _nb_neighb; i++) {
        new_neighb[i] = _neighb[i];
    }
    
    // Ajoute le nouveau voisin
    new_neighb[_nb_neighb] = c;

    // Libère l'ancienne mémoire et met à jour le pointeur
    delete[] _neighb;
    _neighb = new_neighb;
    _nb_neighb++;

    // Appelle récursivement la méthode pour ajouter this comme voisin de c
    c->add_neighb(this);
}

// Méthode pour ajouter deux voisins
void Cell :: add_neighb(Cell* c1, Cell* c2) {
    this->add_neighb(c2);
    this->add_neighb(c1);
}

// Méthode pour ajouter trois voisins
void Cell :: add_neighb(Cell* c1, Cell* c2, Cell* c3){
    this->add_neighb(c3);
    this->add_neighb(c1, c2);
}

// Méthode pour ajouter quatres voisins
void Cell :: add_neighb(Cell* c1, Cell* c2, Cell* c3, Cell* c4){
    this->add_neighb(c4);
    this->add_neighb(c1, c2, c3);
}

// Affichage des coordonnées et des voisins (pour faciliter le débogage)
void Cell :: print() const {
    std::cout << "Cell(" << _x << ", " << _y << ") has " << _nb_neighb << " neighbours: ";
    for (int i = 0; i < _nb_neighb; i++) {
        std::cout << "(" << _neighb[i]->_x << ", " << _neighb[i]->_y << ") ";
    }
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    // Sérialisation de l'objet `cell` dans le flux `os`
    os << "(" << cell._x << "," << cell._y << ")";
    return os; // Retourner le flux permet de chaîner les appels
}

// Opérateur >> pour la désérialisation d'une Cell
std::istream& operator>>(std::istream& is, Cell& cell) {
    // Lire les coordonnées de la cellule, format attendu : (x,y)
    char ch;
    is >> ch >> cell._x >> ch >> cell._y >> ch;  // Format "(x,y)"


    return is;
}
