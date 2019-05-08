#ifndef __SQUARE_KJASHDKJHQWLJKEHJKQASWHNKJANBSHDJKBALKJSDBHASJDHLKJHADASDAHWJSGEWQ__
#define __SQUARE_KJASHDKJHQWLJKEHJKQASWHNKJANBSHDJKBALKJSDBHASJDHLKJHADASDAHWJSGEWQ__

#include <QCoreApplication>
#include <vector>
#include "consts.h"


class Square {
public:
    explicit Square(int);
    Square(int, int);
    Square();

    int row() const;
    int column() const;
    int index() const;

    inline bool operator==(const Square &square) const {
        return square.index() == _index;
    }
    inline bool operator<(const Square &square) const {
        return  _index < square.index();
    }
private:
    int _index;
};

using Squares = std::vector<Square>;

#endif // __SQUARE_KJASHDKJHQWLJKEHJKQASWHNKJANBSHDJKBALKJSDBHASJDHLKJHADASDAHWJSGEWQ__
