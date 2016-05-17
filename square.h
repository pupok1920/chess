#ifndef SQUARE
#define SQUARE
#include <QCoreApplication>
#include <vector>
#include "consts.h"

class Square {
public:
    Square(int row, int column);
    explicit Square(int index);
    Square(): _index(0) {}

    int row() const {
        return _index / BOARD_SIZE;
    }
    int column() const {
        return _index % BOARD_SIZE;
    }
    int index() const {
        return _index;
    }

private:
    int _index;
};

#endif // SQUARE















































