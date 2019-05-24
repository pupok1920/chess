#include "square.h"

Square::Square(int row, int column): _index(row * BOARD_SIZE + column) {}

Square::Square(int index): _index(index) {}

Square::Square(): _index(0) {}

int Square::row() const {
    return _index / BOARD_SIZE;
}

int Square::column() const {
    return _index % BOARD_SIZE;
}

int Square::index() const {
    return _index;
}
