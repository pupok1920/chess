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

    //Piece *type(const PieceType&);
    template<typename T>
    void add(const Square &square) {
        _pieces[square.index()] = std::make_unique<T>();
    }
    void remove(const Square &);
    void replace(const Square &, const Square &);
    Piece* at(const Square &);
    //std::unique_ptr<Piece> at(const Square &);
    void clear();

    Data& operator=(const Data&) = delete;
    Data(const Data&) = delete;

private:
    std::vector<std::unique_ptr<Piece>> _pieces;
};
#endif // __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
