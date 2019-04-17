#include "square.h"

Square::Square(unsigned row, unsigned column): _index(row * BOARD_SIZE + column) {}

Square::Square(unsigned index): _index(index) {}

unsigned Square::row() const {
    return _index / BOARD_SIZE;
}

unsigned Square::column() const {
    return _index % BOARD_SIZE;
}

unsigned Square::index() const {
    return _index;
}
