#ifndef __SQUARE_KJASHDKJHQWLJKEHJKQASWHNKJANBSHDJKBALKJSDBHASJDHLKJHADASDAHWJSGEWQ__
#define __SQUARE_KJASHDKJHQWLJKEHJKQASWHNKJANBSHDJKBALKJSDBHASJDHLKJHADASDAHWJSGEWQ__

#include <QCoreApplication>
#include <vector>
#include "consts.h"


class Square {
public:
    explicit Square(unsigned);
    Square(unsigned, unsigned);
    Square(): _index(0) {}

    unsigned row() const;
    unsigned column() const;
    unsigned index() const;

private:
    unsigned _index;
};

#endif // __SQUARE_KJASHDKJHQWLJKEHJKQASWHNKJANBSHDJKBALKJSDBHASJDHLKJHADASDAHWJSGEWQ__
