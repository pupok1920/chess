#ifndef __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
#define __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
#include <memory>

#include "consts.h"
#include "square.h"
#include "pieces.h"

class Data {
public:
    Data();
    ~Data();

    template<typename T>
    void add(const Square &square, PieceColor color) {
        _pieces[square.index()] = std::make_unique<T>(color);
    }
    void remove(const Square &);
    void replace(const Square &from, const Square &to);
    Piece * at(const Square &) const;
    void clear();

    Data& operator=(const Data &) = delete;
    Data(const Data &) = delete;

private:
    std::vector<std::unique_ptr<Piece>> _pieces;
};
#endif // __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
