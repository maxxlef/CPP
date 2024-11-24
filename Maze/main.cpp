#include "vibes.h"     // Inclusion de la bibliothèque vibes pour le dessin graphique.
#include "Cell.h"      // Inclusion de la définition de la classe Cell.
#include "Maze.h"      // Inclusion de la définition de la structure Maze.
#include "Path.h"      // Inclusion de la définition de la classe Path.
#include <iostream>    // Inclusion de la bibliothèque standard d'entrées/sorties (utilisé ici indirectement).
#include <fstream>     // Inclusion de la bibliothèque standard pour les fichiers.
#include <algorithm>   // Inclusion de la bibliothèque algorithmique pour utiliser std::min et std::max.
#include <queue>
#include <unordered_map>
#include <vector>


// Fonction pour dessiner une "porte" (arc) entre deux cellules du labyrinthe.
// Cette fonction dessine un rectangle entre deux cellules connectées dans le labyrinthe.
// Elle prend en paramètre deux pointeurs de cellules : n1 et n2, qui sont voisines.
void draw_gate(const Cell *n1, const Cell *n2)
{
    // Utilisation de vibes::drawBox pour dessiner un rectangle (porte) entre deux cellules voisines.
    // Le rectangle est dessiné en fonction des coordonnées des cellules n1 et n2.
    // std::min et std::max sont utilisés pour déterminer les bornes du rectangle (pour couvrir les deux cellules).
    // Les valeurs 0.1 et 0.9 sont ajoutées pour ajuster la taille et la position du rectangle à l'intérieur du labyrinthe.
    vibes::drawBox( std::min(n1->_x, n2->_x) + 0.1, std::max(n1->_x, n2->_x) + 0.9, 
                    std::min(n1->_y, n2->_y) + 0.1, std::max(n1->_y, n2->_y) + 0.9,
                    "#EEE8AA[#EEE8AA]"); // Couleur de la porte définie comme "lightGray".
}

// Fonction récursive pour afficher graphiquement le graphe (labyrinthe) à partir d'une cellule donnée.
// La fonction parcourt les cellules voisines et dessine les cellules et les portes (connexions) entre elles.
void display_graph(Cell *cell)
{
    // Dessine la cellule sous forme de carré avec vibes::drawBox.
    // Le carré est dessiné aux coordonnées de la cellule (cell->_x, cell->_y), avec une taille de 1 unité.
    vibes::drawBox(cell->_x, cell->_x + 1, cell->_y, cell->_y + 1, "#8B4513[#8B4513]");
    
    // Marque la cellule comme étant déjà affichée pour éviter les redondances dans le parcours du graphe.
    cell->_displayed = true;

    // Boucle sur chaque cellule voisine de la cellule actuelle.
    for(int i = 0 ; i < cell->_nb_neighb ; i++)
    {
        // Si la cellule voisine n'a pas encore été affichée, on l'affiche en appelant récursivement display_graph.
        if(!cell->_neighb[i]->_displayed)
            display_graph(cell->_neighb[i]);

        // Dessine une porte (arc) entre la cellule actuelle et sa voisine.
        draw_gate(cell, cell->_neighb[i]);
    }
}

Maze create_maze(){
    int size = 10; // Taille du labyrinthe
    Cell** cells = new Cell*[size * size]; // Allocation dynamique d'un tableau de pointeurs de cellules
    for(int x = 0 ; x < size ; x++)
    {
        for(int y = 0 ; y < size ; y++)
        {
            // i * size: index du début de la ligne i (tableau uni-dimensionnel)
            cells[x + y * size] = new Cell(x, y); // Création d'une cellule à la position (i, j)
        }
    }

    // Création des connexions entre les cellules pour former un labyrinthe
    cells[4 + 0*size]->add_neighb(cells[4 + 1*size], cells[3 + 0*size]);
    cells[3 + 0*size]->add_neighb(cells[4 + 0*size], cells[2 + 0*size]);
    cells[2 + 0*size]->add_neighb(cells[3 + 0*size]);
    cells[4 + 1*size]->add_neighb(cells[4 + 0*size], cells[3 + 1*size]);
    cells[3 + 1*size]->add_neighb(cells[4 + 1*size], cells[3 + 2*size]);
    cells[3 + 2*size]->add_neighb(cells[3 + 1*size], cells[2 + 2*size], cells[3 + 3*size]);
    cells[3 + 3*size]->add_neighb(cells[3 + 2*size], cells[3 + 4*size]);
    cells[3 + 4*size]->add_neighb(cells[3 + 3*size], cells[4 + 4*size], cells[3 + 5*size], cells[2 + 4*size]);
    cells[2 + 4*size]->add_neighb(cells[3 + 4*size]);
    cells[4 + 4*size]->add_neighb(cells[3 + 4*size]);
    cells[3 + 5*size]->add_neighb(cells[3 + 4*size]);
    cells[2 + 2*size]->add_neighb(cells[3 + 2*size], cells[2 + 3*size], cells[1 + 2*size]);
    cells[1 + 2*size]->add_neighb(cells[2 + 2*size], cells[1 + 1*size]);
    cells[1 + 1*size]->add_neighb(cells[1 + 2*size], cells[2 + 1*size], cells[1 + 0*size]);
    cells[2 + 1*size]->add_neighb(cells[1 + 1*size]);
    cells[1 + 0*size]->add_neighb(cells[1 + 1*size], cells[0 + 0*size]);
    cells[0 + 0*size]->add_neighb(cells[1 + 0*size]);
    cells[2 + 3*size]->add_neighb(cells[2 + 2*size], cells[1 + 3*size]);
    cells[1 + 3*size]->add_neighb(cells[2 + 3*size], cells[1 + 4*size]);
    cells[1 + 4*size]->add_neighb(cells[1 + 3*size], cells[0 + 4*size]);
    cells[0 + 4*size]->add_neighb(cells[1 + 4*size], cells[0 + 5*size], cells[0 + 3*size]);
    cells[0 + 3*size]->add_neighb(cells[0 + 4*size], cells[0 + 2*size]);
    cells[0 + 2*size]->add_neighb(cells[0 + 3*size], cells[0 + 1*size]);
    cells[0 + 1*size]->add_neighb(cells[0 + 2*size]);
    cells[0 + 5*size]->add_neighb(cells[0 + 4*size], cells[0 + 6*size]);
    cells[0 + 6*size]->add_neighb(cells[0 + 5*size], cells[1 + 6*size]);
    cells[1 + 6*size]->add_neighb(cells[0 + 6*size], cells[1 + 7*size]);
    cells[1 + 7*size]->add_neighb(cells[1 + 6*size], cells[2 + 7*size], cells[1 + 8*size], cells[0 + 7*size]);
    cells[0 + 7*size]->add_neighb(cells[1 + 7*size], cells[0 + 8*size]);
    cells[1 + 8*size]->add_neighb(cells[1 + 7*size]);
    cells[0 + 8*size]->add_neighb(cells[0 + 7*size]);
    cells[2 + 7*size]->add_neighb(cells[1 + 7*size], cells[3 + 7*size], cells[2 + 8*size]);
    cells[2 + 8*size]->add_neighb(cells[2 + 7*size], cells[3 + 8*size]);
    cells[3 + 8*size]->add_neighb(cells[2 + 8*size], cells[4 + 8*size]);
    cells[4 + 8*size]->add_neighb(cells[3 + 8*size]);
    cells[3 + 7*size]->add_neighb(cells[2 + 7*size], cells[3 + 6*size]);
    cells[3 + 6*size]->add_neighb(cells[3 + 7*size], cells[4 + 6*size], cells[2 + 6*size]);
    cells[2 + 6*size]->add_neighb(cells[3 + 6*size], cells[2 + 5*size]);
    cells[2 + 5*size]->add_neighb(cells[2 + 6*size], cells[1 + 5*size]);
    cells[1 + 5*size]->add_neighb(cells[2 + 5*size]);
    cells[4 + 6*size]->add_neighb(cells[3 + 6*size], cells[4 + 5*size], cells[4 + 7*size]);
    cells[4 + 5*size]->add_neighb(cells[4 + 6*size], cells[5 + 5*size]);
    cells[5 + 5*size]->add_neighb(cells[4 + 5*size], cells[5 + 6*size], cells[5 + 4*size]);
    cells[5 + 4*size]->add_neighb(cells[5 + 5*size], cells[5 + 3*size]);
    cells[5 + 3*size]->add_neighb(cells[5 + 4*size], cells[4 + 3*size], cells[6 + 3*size]);
    cells[6 + 3*size]->add_neighb(cells[5 + 3*size], cells[6 + 4*size]);
    cells[6 + 4*size]->add_neighb(cells[6 + 3*size], cells[7 + 4*size]);
    cells[7 + 4*size]->add_neighb(cells[6 + 4*size], cells[7 + 5*size]);
    cells[7 + 5*size]->add_neighb(cells[7 + 4*size], cells[6 + 5*size], cells[8 + 5*size]);
    cells[8 + 5*size]->add_neighb(cells[7 + 5*size]);
    cells[6 + 5*size]->add_neighb(cells[7 + 5*size]);
    cells[4 + 3*size]->add_neighb(cells[5 + 3*size], cells[4 + 2*size]);
    cells[4 + 2*size]->add_neighb(cells[4 + 3*size]);
    cells[5 + 6*size]->add_neighb(cells[5 + 5*size], cells[6 + 6*size]);
    cells[6 + 6*size]->add_neighb(cells[5 + 6*size], cells[6 + 7*size]);
    cells[6 + 7*size]->add_neighb(cells[6 + 6*size], cells[7 + 7*size]);
    cells[7 + 7*size]->add_neighb(cells[6 + 7*size], cells[8 + 7*size]);
    cells[6 + 8*size]->add_neighb(cells[7 + 8*size], cells[5 + 8*size]);
    cells[7 + 8*size]->add_neighb(cells[6 + 8*size]);
    cells[5 + 8*size]->add_neighb(cells[6 + 8*size], cells[5 + 7*size]);
    cells[5 + 7*size]->add_neighb(cells[5 + 8*size], cells[4 + 7*size]);
    cells[4 + 7*size]->add_neighb(cells[5 + 7*size], cells[4 + 6*size]);
    cells[8 + 7*size]->add_neighb(cells[7 + 7*size], cells[8 + 6*size]);
    cells[8 + 6*size]->add_neighb(cells[8 + 7*size], cells[9 + 6*size], cells[7 + 6*size]);
    cells[7 + 6*size]->add_neighb(cells[8 + 6*size]);
    cells[9 + 6*size]->add_neighb(cells[8 + 6*size], cells[9 + 5*size], cells[9 + 7*size]);
    cells[9 + 7*size]->add_neighb(cells[9 + 6*size], cells[9 + 8*size]);
    cells[9 + 8*size]->add_neighb(cells[9 + 7*size], cells[8 + 8*size]);
    cells[8 + 8*size]->add_neighb(cells[9 + 8*size]);
    cells[9 + 5*size]->add_neighb(cells[9 + 6*size], cells[9 + 4*size]);
    cells[9 + 4*size]->add_neighb(cells[9 + 5*size], cells[8 + 4*size]);
    cells[8 + 4*size]->add_neighb(cells[9 + 4*size], cells[8 + 3*size]);
    cells[8 + 3*size]->add_neighb(cells[8 + 4*size], cells[7 + 3*size], cells[8 + 2*size]);
    cells[8 + 2*size]->add_neighb(cells[8 + 3*size], cells[9 + 2*size]);
    cells[9 + 2*size]->add_neighb(cells[8 + 2*size], cells[9 + 1*size], cells[9 + 3*size]);
    cells[9 + 3*size]->add_neighb(cells[9 + 2*size]);
    cells[9 + 1*size]->add_neighb(cells[9 + 2*size], cells[8 + 1*size], cells[9 + 0*size]);
    cells[9 + 0*size]->add_neighb(cells[9 + 1*size]);
    cells[8 + 1*size]->add_neighb(cells[9 + 1*size], cells[8 + 0*size], cells[7 + 1*size]);
    cells[7 + 1*size]->add_neighb(cells[8 + 1*size]);
    cells[8 + 0*size]->add_neighb(cells[8 + 1*size]);
    cells[7 + 3*size]->add_neighb(cells[8 + 3*size], cells[7 + 2*size]);
    cells[7 + 2*size]->add_neighb(cells[7 + 3*size], cells[6 + 2*size]);
    cells[6 + 2*size]->add_neighb(cells[7 + 2*size], cells[6 + 1*size], cells[5 + 2*size]);
    cells[5 + 2*size]->add_neighb(cells[6 + 2*size]);
    cells[6 + 1*size]->add_neighb(cells[6 + 2*size], cells[5 + 1*size], cells[6 + 0*size]);
    cells[6 + 0*size]->add_neighb(cells[6 + 1*size], cells[7 + 0*size]);
    cells[7 + 0*size]->add_neighb(cells[6 + 0*size]);
    cells[5 + 1*size]->add_neighb(cells[6 + 1*size], cells[5 + 0*size]);
    cells[5 + 0*size]->add_neighb(cells[5 + 1*size]);


    // Print des cellules
    for(int i = 0 ; i < size ; i++)
    {
        for(int j = 0 ; j < size ; j++)
        {
            cells[i * size + j]->print();
        }
    }

    // Création de la structure Maze avec la cellule de départ et la cellule d'arrivée
    Maze maze(cells[4 + 0*size], cells[5 + 0*size]);
    return maze;

}

Maze read_maze(const std::string& file_name){
    std::ifstream file(file_name);
    std::map<std::pair<int, int>, Cell*> cells;  // Dictionnaire pour stocker les cellules par coordonnées
    std::string line;

    Maze maze(nullptr, nullptr);  // Initialisation du labyrinthe avec des pointeurs nuls
    maze.start = new Cell(0,0);  // Création de la cellule de départ
    maze.end = new Cell(0,0);    // Création de la cellule d'arrivée

    char cd;

    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << file_name << std::endl;
        return maze;
    }
    getline(file, line);  // Passer la première ligne
    std::cout << line << std::endl;
    file >> *maze.start >> std::ws;
    std::pair<int, int> cell_key = std::make_pair(maze.start ->_x, maze.start ->_y);
    // Vérifier si la cellule existe déjà dans le dictionnaire
    if (cells.find(cell_key) == cells.end()) {
        cells[cell_key] = new Cell(maze.start ->_x, maze.start ->_y);
    }
    getline(file, line);  // Passer la troisème ligne
    std::cout << line << std::endl;
    file >> *maze.end>> std::ws;
    cell_key = std::make_pair(maze.end ->_x, maze.end ->_y);
    // Vérifier si la cellule existe déjà dans le dictionnaire
    if (cells.find(cell_key) == cells.end()) {
        cells[cell_key] = new Cell(maze.end ->_x, maze.end ->_y);
    }
    getline(file, line);  // Passer la quatrième ligne
    //print la ligne
    std::cout << line << std::endl;
    // Parcourir les cellules
    while (!file.eof()) {
        Cell cell;
        file >> cell;  // Lecture des coordonnées de la cellule
        cell_key = std::make_pair(cell._x, cell._y);
        // Vérifier si la cellule existe déjà dans le dictionnaire
        if (cells.find(cell_key) == cells.end()) {
            cells[cell_key] = new Cell(cell._x, cell._y);
        }

        // Lire le nombre de voisins
        file >> cell._nb_neighb;

        for (int i = 0; i < cell._nb_neighb; ++i) {
            Cell neighb;
            if (!(file >> neighb)) break;  // Lecture d'un voisin
            auto neighb_key = std::make_pair(neighb._x, neighb._y);

            // Vérifier si le voisin existe déjà dans le dictionnaire
            if (cells.find(neighb_key) == cells.end()) {
                cells[neighb_key] = new Cell(neighb._x, neighb._y);
            }

            // Ajouter le voisin à la cellule courante
            cells[cell_key]->add_neighb(cells[neighb_key]);
            cells[cell_key]->print();
        }
        cell_key = std::make_pair(maze.start ->_x, maze.start ->_y);
        maze.start = cells[cell_key];
        cell_key = std::make_pair(maze.end ->_x, maze.end ->_y);
        maze.end = cells[cell_key];
        file >> std::ws;  // Lire les espaces blancs
        
    }

    return maze;
}

bool find_path(Cell *c, Cell *cf, Path *p) {
    // Si la cellule courante est l'objectif, on a trouvé le chemin
    if (c == cf) {
        p->add_to_path(c);  // Ajouter l'objectif au chemin
        std::cout << "Solution trouvée" << std::endl;
        return true;  // Retourne vrai pour indiquer que l'objectif est atteint
    }

    c->_in_path = true;  // Marquer la cellule comme visitée

    // Exploration des voisins
    for (int i = 0; i < c->_nb_neighb; i++) {
        // Vérifier si le voisin n'a pas déjà été visité
        if (!c->_neighb[i]->_in_path) {
            // Appel récursif pour explorer le voisin
            if (find_path(c->_neighb[i], cf, p)) {
                // Si un chemin est trouvé, ajouter la cellule courante au chemin
                p->add_to_path(c);
                std::cout << "x : " << c->_x << " y : " << c->_y << std::endl;
                return true;  // Retourner true dès qu'un chemin est trouvé
            }
        }
    }

    return false;  // Retourne false si aucun chemin n'est trouvé
}


bool find_shortest_path_bfs(Cell* start, Cell* end, Path* path) {
    // Queue pour le BFS : chaque élément est une cellule à visiter
    std::queue<Cell*> to_visit;
    // Map pour enregistrer les cellules déjà visitées
    std::unordered_map<Cell*, bool> visited;
    // Map pour stocker le prédécesseur de chaque cellule, pour reconstruire le chemin
    std::unordered_map<Cell*, Cell*> predecessors;

    // Initialisation : marquer la cellule de départ comme visitée
    visited[start] = true;
    to_visit.push(start);

    // Commencer le BFS
    while (!to_visit.empty()) {
        Cell* current = to_visit.front();
        to_visit.pop();

        // Si on a atteint la cellule de fin, on reconstruit le chemin
        if (current == end) {
            break;
        }

        // Explorer les voisins de la cellule actuelle
        for (int i = 0; i < current->_nb_neighb; ++i) {
            Cell* neighbor = current->_neighb[i];

            // Si le voisin n'a pas encore été visité, on l'ajoute à la queue
            if (visited.find(neighbor) == visited.end()) {
                visited[neighbor] = true;
                predecessors[neighbor] = current;  // Enregistrer le prédécesseur
                to_visit.push(neighbor);
            }
        }
    }

    // Si on n'a pas trouvé de chemin (la cellule de fin n'a pas été atteinte)
    if (visited.find(end) == visited.end()) {
        std::cout << "Aucun chemin trouvé entre les cellules." << std::endl;
        return false;
    }

    // Reconstruire le chemin à partir des prédécesseurs
    Cell* current = end;
    while (current != nullptr) {
        path->add_to_path(current);  // Ajouter la cellule au chemin
        current = predecessors[current];  // Remonter le chemin
    }

    return true;
}

// Fonction pour afficher le labyrinthe graphiquement
void display(Maze m, float x_max, float y_max) {
    vibes::beginDrawing(); // Début du dessin
    vibes::newFigure("Maze"); // Création d'une nouvelle figure nommée "Maze"
    vibes::setFigureProperties("Maze", vibesParams("x", 100, "y", 100, "width", 400, "height", 400)); // Propriétés de la figure
    vibes::axisLimits(0. -0.5, x_max +0.5, 0. -0.5, y_max +0.5); // Limites de l'axe pour bien voir le labyrinthe
    display_graph(m.start); // Affichage graphique du labyrinthe à partir de la cellule de départ

}

void save_cell(Cell *cell, std::ofstream& f) {
    // Vérifier si la cellule a déjà été écrite pour éviter de la parcourir plusieurs fois
    if (cell->_written) {
        return; // Si la cellule est déjà écrite, on quitte la fonction
    }

    // Sérialiser la cellule actuelle
    f << *cell;  // Coordonnées de la cellule
    f << cell->_nb_neighb;  // Nombre de voisins
    
    // Sérialiser les voisins
    for (int i = 0; i < cell->_nb_neighb; ++i) {
        f << *cell->_neighb[i];  // Coordonnées du voisin
    }

    f << std::endl;  // Saut de ligne après la sérialisation de la cellule

    // Marquer la cellule comme écrite
    cell->_written = true;

    // Appel récursif pour chaque voisin non écrit
    for (int i = 0; i < cell->_nb_neighb; ++i) {
        if (!cell->_neighb[i]->_written) {  // Vérifier si le voisin n'a pas été écrit
            save_cell(cell->_neighb[i], f);  // Appel récursif pour ce voisin
        }
    }
}

void save_maze(const Maze& maze, const std::string& file_name) {
    std::ofstream file(file_name);  // 'std::ofstream' est dans l'espace de noms 'std'
    if(file.is_open()) {
        file << "# Start:" << std::endl;
        file << *maze.start << std::endl;
        file << "# End:" << std::endl;
        file << *maze.end << std::endl;
        file << "# Cells:" << std::endl;
        save_cell(maze.start, file);
        file.close();
    }
    else {
        std::cerr << "Error: could not open file " << file_name << std::endl;  // 'std::cerr' est dans l'espace de noms 'std'
    }
}

int main()
{
    Maze m = read_maze("maze_10x10.txt");
    // debug
    std::cout << "start : " << m.start->_x << " " << m.start->_y << std::endl;
    std::cout << "end : " << m.end->_x << " " << m.end->_y << std::endl;
    std::cout << "nb_neighb : " << m.start->_nb_neighb << std::endl;
    std::cout << "nb_neighb : " << m.end->_nb_neighb << std::endl;
    for (int i = 0; i < m.start->_nb_neighb; i++) {
        std::cout << "neighb : " << m.start->_neighb[i]->_x << " " << m.start->_neighb[i]->_y << std::endl;
    }
    display(m,10,10); // Affichage graphique du labyrinthe
    save_maze(m, "maze.txt");
    Path p(m.end); // Création d'un chemin à partir de la cellule de départ
    find_shortest_path_bfs(m.start, m.end, &p); // Recherche d'un chemin entre la cellule de départ et la cellule d'arrivée
    p.display_path(); // Affichage graphique du chemin complet
    int xstart = m.start->_x;
    int ystart = m.start->_y;
    int xend = m.end->_x;
    int yend = m.end->_y;
    //afficher les x et y 
    std::cout << "xstart : " << xstart << std::endl;
    std::cout << "ystart : " << ystart << std::endl;
    std::cout << "xend : " << xend << std::endl;
    std::cout << "yend : " << yend << std::endl;
    vibes::drawCircle(xend + 0.5, yend + 0.5, 0.3, "#DAA520[#FFD700]"); // Dessin d'un cercle rouge à la position (0.5, 0.5) avec un rayon de 0.3
    vibes::drawCircle(xstart + 0.5 , ystart + 0.5, 0.3, "#8B4513[#B8860B]"); // Dessin d'un cercle vert à la position (3.5, 3.5) avec un rayon de 0.3

    vibes::endDrawing(); // Fin du dessin
    return EXIT_SUCCESS;
}
