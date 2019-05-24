#ifndef __VALIDATORSVUIHVEUVJKDVSBVKSVDJ__
#define __VALIDATORSVUIHVEUVJKDVSBVKSVDJ__

#include "square.h"

class Data;

class Validator {
public:
    Validator();
    ~Validator();

    bool isPawnMoveValid(const Squares &moves, const Square &from, const Square &to);
    bool isOrdinaryMoveValid(const Squares &moves, const Square &to);
    bool isEnPassantPossible() const;

    int getEnPassantPiece();

private:
    bool findIn(const Squares &, const Square &) const;

private:
    int _enPassantSquare;
    int _enPassantPiece;
};
#endif
