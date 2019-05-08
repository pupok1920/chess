#include "validator.h"
#include "pieces.h"
#include "data.h"

Validator::Validator() {}

Validator::~Validator() {}

bool Validator::isMoveValid(const Data *data, const Square &from, const Square &to) const {
    const Piece *pieceFrom = data->at(from);
    const Piece *pieceTo = data->at(to);

    bool result = false;
    Squares moves = pieceFrom->moves(from, data);
    if (std::find(moves.begin(), moves.end(), to) != moves.end()) {
        result = (pieceTo == nullptr) || (pieceTo->color() != pieceFrom->color());
    }
    return result;
}
