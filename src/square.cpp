#include "square.h"

Square::Square(unsigned int row,unsigned int column): _index(row * BOARD_SIZE + column) {}

Square::Square(unsigned int index): _index(index) {}
