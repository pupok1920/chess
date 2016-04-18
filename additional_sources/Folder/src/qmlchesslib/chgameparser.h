#ifndef CHGAMEPARSER_H
#define CHGAMEPARSER_H

#include "chlib.h"
#include "chparserbase.h"
#include "chsquare.h"

class QMLCHESSLIB_COMMON_DLLSPEC ChGameParser : public ChParserBase
{
public:
    ChGameParser();

    ~ChGameParser();

    typedef std::pair<ChSquare, ChSquare> Move;
    typedef std::vector<Move> Moves;

    Moves load(const QString &fileName) const;
    void save(const QString &fileName, const Moves &moves) const;

private:
    void domToMoves(const QDomDocument &doc, Moves &moves) const;
    void movesToDom(const Moves &moves, QDomDocument &doc) const;
};

#endif // CHGAMEPARSER_H
