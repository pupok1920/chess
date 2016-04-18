#include <QCoreApplication>
#include <QUndoCommand>
#include <QUndoStack>

#include "../test.h"

#include "chmovecommand.h"
#include "chboarddata.h"
#include "chgameparser.h"

Q_DECLARE_METATYPE(ChGameParser::Moves)

class ChMoveCommandTest : public QObject
{
    Q_OBJECT

public:
    ChMoveCommandTest();

private Q_SLOTS:
    void testMoves_data();
    void testMoves();
    void testMovesIncorrect();

private:
    void initData(const ChPiecesTestData &d);
    void checkData(const ChPiecesTestData &d);

private:
    QUndoStack _stack;
    ChBoardData _data;
};

ChMoveCommandTest::ChMoveCommandTest()
{
}

void ChMoveCommandTest::testMoves_data()
{
    QTest::addColumn<ChPiecesTestData>("init");
    QTest::addColumn<ChGameParser::Moves>("moves");
    QTest::addColumn<ChPiecesTestData>("final");

    {
        ChPiecesTestData init;
        init.insert(ChSquare(2,3), _data.pawn(CH_WHITE_COLOR));
        init.insert(ChSquare(3,4), _data.pawn(CH_WHITE_COLOR));
        init.insert(ChSquare(3,5), _data.bishop(CH_WHITE_COLOR));
        init.insert(ChSquare(4,3), _data.pawn(CH_BLACK_COLOR));
        init.insert(ChSquare(5,3), _data.queen(CH_BLACK_COLOR));
        init.insert(ChSquare(5,5), _data.knight(CH_BLACK_COLOR));

        ChGameParser::Moves moves;
        moves.push_back(std::make_pair(ChSquare(2, 3), ChSquare(3, 3)));
        moves.push_back(std::make_pair(ChSquare(4, 3), ChSquare(3, 4)));
        moves.push_back(std::make_pair(ChSquare(3, 5), ChSquare(5, 3)));
        moves.push_back(std::make_pair(ChSquare(3, 4), ChSquare(2, 4)));
        moves.push_back(std::make_pair(ChSquare(3, 3), ChSquare(4, 3)));
        moves.push_back(std::make_pair(ChSquare(5, 5), ChSquare(4, 3)));

        ChPiecesTestData final;
        final.insert(ChSquare(5,3), _data.bishop(CH_WHITE_COLOR));
        final.insert(ChSquare(4,3), _data.knight(CH_BLACK_COLOR));
        final.insert(ChSquare(2,4), _data.pawn(CH_BLACK_COLOR));

        QTest::newRow("moves 1") << init << moves << final;
    }
    {
        ChPiecesTestData init;
        init.insert(ChSquare(3,3), _data.rook(CH_WHITE_COLOR));
        init.insert(ChSquare(3,4), _data.king(CH_WHITE_COLOR));
        init.insert(ChSquare(4,3), _data.rook(CH_BLACK_COLOR));
        init.insert(ChSquare(4,4), _data.king(CH_BLACK_COLOR));

        ChGameParser::Moves moves;
        moves.push_back(std::make_pair(ChSquare(3, 3), ChSquare(4, 3)));
        moves.push_back(std::make_pair(ChSquare(4, 4), ChSquare(3, 4)));
        moves.push_back(std::make_pair(ChSquare(4, 3), ChSquare(3, 3)));
        moves.push_back(std::make_pair(ChSquare(3, 4), ChSquare(3, 3)));

        ChPiecesTestData final;
        final.insert(ChSquare(3,3), _data.king(CH_BLACK_COLOR));

        QTest::newRow("moves 2") << init << moves << final;
    }}

void ChMoveCommandTest::testMoves()
{
    QFETCH(ChPiecesTestData, init);
    QFETCH(ChGameParser::Moves, moves);
    QFETCH(ChPiecesTestData, final);

    initData(init);
    for (ChGameParser::Moves::iterator it = moves.begin(); it != moves.end(); ++it) {
        ChMoveCommand* cmd = new ChMoveCommand(&_data, it->first, it->second, 0);
        _stack.push(cmd);
    }

    checkData(final);
    _stack.setIndex(0);
    checkData(init);
    _stack.setIndex(_stack.count());
    checkData(final);
    _stack.setIndex(0);
    checkData(init);
    _stack.setIndex(_stack.count());
    checkData(final);
    _stack.setIndex(0);
    checkData(init);
}

void ChMoveCommandTest::testMovesIncorrect()
{

    ChMoveCommand cmd(&_data, ChSquare(0, 0), ChSquare(1, 1), 0);
    QVERIFY_EXCEPTION_THROWN(cmd.redo(), ChLogicException);
    QVERIFY_EXCEPTION_THROWN(cmd.undo(), ChLogicException);

    ChPiecesTestData init;
    init.insert(ChSquare(3,3), _data.rook(CH_WHITE_COLOR));
    init.insert(ChSquare(3,4), _data.king(CH_WHITE_COLOR));
    init.insert(ChSquare(4,3), _data.rook(CH_BLACK_COLOR));
    init.insert(ChSquare(4,4), _data.king(CH_BLACK_COLOR));

    initData(init);
    ChMoveCommand cmd1(&_data, ChSquare(3, 3), ChSquare(3, 4), 0);
    cmd1.redo();
    const ChPiece *p = _data.remove(ChSquare(3, 4));
    QVERIFY_EXCEPTION_THROWN(cmd1.undo(), ChLogicException);
    _data.add(ChSquare(3, 4), p);
    cmd1.undo();
    checkData(init);
}

void ChMoveCommandTest::initData(const ChPiecesTestData &d)
{
    _data.clear();
    _stack.clear();

    for (ChPiecesTestData::const_iterator it = d.begin(); it != d.end(); ++it) {
        _data.add(it.key(), it.value());
    }
}

void ChMoveCommandTest::checkData(const ChPiecesTestData &d)
{
    for (int i = 0; i < CH_BOARD_SIZE; ++i) {
        for (int j = 0; j < CH_BOARD_SIZE; ++j) {
            const ChPiece *p = _data.at(ChSquare(i, j));
            const ChPiece *p1 = 0;
            ChPiecesTestData::const_iterator it = d.find(ChSquare(i, j));
            if (it != d.end()) {
                p1 = it.value();
            }
            QCOMPARE(p1, p);
        }
    }
}

QTEST_MAIN(ChMoveCommandTest)

#include "tst_chmovecommandtest.moc"
