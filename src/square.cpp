#include "square.h"

Square::Square(int row, int column): _index(row * BOARD_SIZE + column) {}

Square::Square(int index): _index(index) {}
