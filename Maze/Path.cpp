
#include "Path.h"     // Inclusion de la définition de la classe Path.

// Constructeur pour initialiser un nœud du chemin
Path::Path(const Cell *c) : _c(c) {
    if (_head == nullptr) {
        _head = this;  // Si c'est le premier nœud, _head pointe vers ce nœud
    }
}

// Destructeur pour libérer la mémoire
Path::~Path() {
    if(_next != nullptr)
        delete _next;  // Supprimer le nœud actuel
}

void Path::add_to_path(const Cell *c) {
    // On doit ajouter à la fin
    Path* current = _head;
    while (current->_next != nullptr) { // Parcours de la liste jusqu'au dernier nœud
        // En C++, l'opérateur -> permet d'accéder aux membres (attributs ou méthodes)
        // d'un objet via un pointeur
        current = current->_next;
    }
    // Ajout du nouveau nœud à la fin de la liste
    current->_next = new Path(c);
}


void Path::display_link(const Cell *n1, const Cell *n2) {
    // Dessine un lien entre les cellules n1 et n2
    int min_x = std::min(n1->_x, n2->_x);
    int max_x = std::max(n1->_x, n2->_x);
    int min_y = std::min(n1->_y, n2->_y);
    int max_y = std::max(n1->_y, n2->_y);
    vibes::drawBox(min_x - 0.1 +0.5, max_x + 0.1+0.5, min_y - 0.1+0.5, max_y + 0.1+0.5, "#00CED1[#00CED1]");
}

void Path::display_path() {
    // Si la liste est vide, il n'y a pas de chemin à afficher
    if (_head == nullptr) {
        std::cout << "No path to display" << std::endl;
        return;
    }

    // Parcours de la liste pour afficher les liens entre les cellules
    Path* current = _head;
    while (current->_next != nullptr) {
        display_link(current->_c, current->_next->_c);
        // print
        std::cout << "x : " << current->_c->_x << " y : " << current->_c->_y << std::endl;
        current = current->_next;
    }
}
