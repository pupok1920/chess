#ifndef CHSQUARE_H
#define CHSQUARE_H

#include <vector>

#include <QCoreApplication>

#include "chlib.h"
#include "chconsts.h"

class QMLCHESSLIB_COMMON_DLLSPEC ChSquare {
    Q_DECLARE_TR_FUNCTIONS(ChSquare)
public:
    ChSquare(int row, int column);
    explicit ChSquare(int index);
    ChSquare():_index(0) {}
    int row() const {
        return _index / CH_BOARD_SIZE;
    }
    int column() const {
        return _index % CH_BOARD_SIZE;
    }
    int index() const {
        return _index;
    }
    bool operator==(const ChSquare &square) const {
        return square.index() == _index;
    }
    bool operator<(const ChSquare &square) const {
        return  _index < square.index();
    }
private:
    int _index;
};

typedef std::vector<ChSquare> ChSquares;

#endif // CHSQUARE_H



