#include "chgameparser.h"

#define CH_GAME_SCHEMA_FILE_NAME ":/schemas/game.xsd"
#define CH_GAME_ROOT "Game"
#define CH_GAME_MOVE "Move"
#define CH_GAME_FROM "from"
#define CH_GAME_TO "to"
#define CH_PROCESSING_INSTRUCTION "version='1.0' encoding='UTF-8'"

/*!
 * \class ChGameParser
 * \brief Loads and Saves chess game.
 */
ChGameParser::ChGameParser()
{

}

ChGameParser::~ChGameParser()
{

}

/*!
 * \brief Loads chess game.
 * \param fileName - file to load from. XML file format is defined in game.xsd.
 * \return game moves.
 * \exception ChException in case if file cannot be successfully parsed (IO errors, incorrect moves
 * etc.).
 */
ChGameParser::Moves ChGameParser::load(const QString &fileName) const
{
    // validate using schema
    validate(CH_GAME_SCHEMA_FILE_NAME, fileName);
    // load from file
    QDomDocument doc = loadToDom(fileName);
    // parse loaded data
    Moves moves;
    domToMoves(doc, moves);
    return moves;
}

/*!
 * \brief Saves chess game.
 * \param fileName - target file.
 * \param moves - game moves.
 * \exception ChException in case if file cannot be successfully saved (IO errors, etc.).
 */
void ChGameParser::save(const QString &fileName,
    const ChGameParser::Moves &moves) const
{
    QDomDocument doc;
    movesToDom(moves, doc);
    saveFile(fileName, doc, CH_GAME_SCHEMA_FILE_NAME);
}

void ChGameParser::domToMoves(const QDomDocument &doc,
    ChGameParser::Moves &moves) const
{
    moves.clear();
    QDomElement e = doc.documentElement().firstChildElement(CH_GAME_MOVE);
    while (!e.isNull()) {
        // Value is already validated using XML Schema
        int from = e.attribute(CH_GAME_FROM).toInt();
        int to = e.attribute(CH_GAME_TO).toInt();
        moves.push_back(std::make_pair(ChSquare(from), ChSquare(to)));
        e = e.nextSiblingElement(CH_GAME_MOVE);
    }
}
struct Ch_Mover {
    explicit Ch_Mover(QDomDocument &doc):_doc(doc)
    {
    }
    void operator()(const ChGameParser::Move &move)
    {
        QDomElement e = _doc.createElement(CH_GAME_MOVE);
        e.setAttribute(CH_GAME_FROM, move.first.index());
        e.setAttribute(CH_GAME_TO, move.second.index());
        _doc.documentElement().appendChild(e);
    }
private:
    QDomDocument &_doc;
};

void ChGameParser::movesToDom(const Moves &moves, QDomDocument &doc) const
{
    doc.clear();
    doc.appendChild(doc.createProcessingInstruction("xml", CH_PROCESSING_INSTRUCTION));
    QDomElement root = doc.createElement(CH_GAME_ROOT);
    doc.appendChild(root);
    std::for_each(moves.begin(), moves.end(), Ch_Mover(doc));
}

