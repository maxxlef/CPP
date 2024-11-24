#ifndef MAZE_H
#define MAZE_H


struct Maze {
    Cell* start = nullptr;  // Pointeur vers la cellule de départ
    Cell* end = nullptr;    // Pointeur vers la cellule d'arrivée
    

    // Constructeur
    Maze(Cell* startCell, Cell* endCell) : start(startCell), end(endCell) {}
};

#endif // MAZE_H
