#ifndef CHSIMPLEVALIDATOR_H
#define CHSIMPLEVALIDATOR_H

#include "chlib.h"
#include "chvalidator.h"

class QMLCHESSLIB_COMMON_DLLSPEC ChSimpleValidator: public ChValidator
{
public:
    bool isMoveValid(const ChBoardData *data, const ChSquare &from,
        const ChSquare& to, ChPieceColor color) const;
};

#endif // CHSIMPLEVALIDATOR_H
