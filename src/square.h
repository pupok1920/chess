#ifndef __SQUARE_KJASHDKJHQWLJKEHJKQASWHNKJANBSHDJKBALKJSDBHASJDHLKJHADASDAHWJSGEWQ__
#define __SQUARE_KJASHDKJHQWLJKEHJKQASWHNKJANBSHDJKBALKJSDBHASJDHLKJHADASDAHWJSGEWQ__

#include <QCoreApplication>
#include <vector>
#include "consts.h"


class Square {
public:
    explicit Square(unsigned int);
    Square(unsigned int, unsigned int);
    Square(): _index(0) {}

    unsigned int row() const {
        return _index / BOARD_SIZE;
    }
    unsigned int column() const {
        return _index % BOARD_SIZE;
    }
    unsigned int index() const {
        return _index;
    }

private:
    unsigned int _index;
};

#endif // __SQUARE_KJASHDKJHQWLJKEHJKQASWHNKJANBSHDJKBALKJSDBHASJDHLKJHADASDAHWJSGEWQ__
