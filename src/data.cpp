#include <utility>

#include "data.h"

Data::Data()
    :_pieces(BOARD_SIZE * BOARD_SIZE) {}

Data::~Data() {}

void Data::remove(const Square &square) {
    _pieces[square.index()] = nullptr;
}

void Data::replace(const Square &squareFrom, const Square &squareTo) {
    _pieces[squareTo.index()] = std::move(_pieces[squareFrom.index()]);
}

Piece* Data::at(const Square &square) {
    return _pieces.at(square.index()).get();
//std::shared_ptr<Piece> Data::at(const Square &square) {
    //return _pieces.at(square.index());
}

void Data::clear()
{
    for(unsigned i = 0; i < _pieces.size(); ++i) {
        _pieces[i] = nullptr;
    }
}
