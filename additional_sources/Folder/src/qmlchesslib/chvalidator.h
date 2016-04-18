#ifndef CHVALIDATOR_H
#define CHVALIDATOR_H

#include "chlib.h"
#include "chconsts.h"

class ChBoardData;
class ChSquare;

class QMLCHESSLIB_COMMON_DLLSPEC ChValidator
{
public:
    ~ChValidator();
    virtual bool isMoveValid(const ChBoardData *data, const ChSquare &from,
        const ChSquare& to, ChPieceColor color) const = 0;
};

#endif // CHVALIDATOR_H
