#include "../test.h"

class ChPiecesTest : public QObject
{
    Q_OBJECT

public:
    ChPiecesTest();

private Q_SLOTS:
    void testCasePiece_data();
    void testCasePiece();

    void testCasePawnIncorrect();
    void testCaseKingIncorrect();
    void testCaseRookIncorrect();
    void testCaseBishopIncorrect();
    void testCaseQueenIncorrect();
    void testCaseKnightIncorrect();

private:
    void initData(const ChPiecesTestData &d);

private:
    ChBoardData _data;
};

ChPiecesTest::ChPiecesTest()
{
}

void ChPiecesTest::testCasePiece_data()
{
    QTest::addColumn<ChPiecesTestData>("position");
    QTest::addColumn<ChSquare>("pieceToMove");
    QTest::addColumn<ChSquares>("moves");

    {
        ChPiecesTestData d;
        d.insert(ChSquare(1,4), _data.pawn(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(2, 4));
        moves.push_back(ChSquare(3, 4));

        QTest::newRow("pawn e2") << d  << ChSquare(1,4) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(2,4), _data.pawn(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(3, 4));

        QTest::newRow("pawn e3") << d  << ChSquare(2,4) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(7,4), _data.pawn(CH_WHITE_COLOR));

        QTest::newRow("pawn e8") << d  << ChSquare(7,4) << ChSquares();
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(2,4), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(3,4), _data.pawn(CH_WHITE_COLOR));

        QTest::newRow("pawn e2 blocked by white") << d  << ChSquare(2,4) << ChSquares();
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(1,4), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(2,4), _data.pawn(CH_WHITE_COLOR));

        QTest::newRow("pawn e2 blocked by white") << d  << ChSquare(1,4) << ChSquares();
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(2,4), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(3,4), _data.pawn(CH_BLACK_COLOR));

        QTest::newRow("pawn e2 blocked by black") << d  << ChSquare(2, 4) << ChSquares();
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(2,4), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(3,4), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(3,3), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(3,5), _data.pawn(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(3,3));
        moves.push_back(ChSquare(3,5));

        QTest::newRow("pawn e2 blocked by black + 2 blacks on diag") << d << ChSquare(2,4) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(2,4), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(3,4), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(3,3), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(3,5), _data.pawn(CH_WHITE_COLOR));

        QTest::newRow("pawn e2 blocked by white + 2 whites on diag") << d
            << ChSquare(2,4) << ChSquares();
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(6,4), _data.pawn(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(5, 4));
        moves.push_back(ChSquare(4, 4));

        QTest::newRow("pawn e7") << d  << ChSquare(6,4) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(5,4), _data.pawn(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(4, 4));

        QTest::newRow("pawn e6") << d  << ChSquare(5,4) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(0,4), _data.pawn(CH_BLACK_COLOR));

        QTest::newRow("pawn e1") << d  << ChSquare(0,4) << ChSquares();
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(5,4), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(4,4), _data.pawn(CH_BLACK_COLOR));

        QTest::newRow("pawn e6 blocked by black") << d  << ChSquare(5,4) << ChSquares();
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(6,4), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(5,4), _data.pawn(CH_BLACK_COLOR));

        QTest::newRow("pawn e7 blocked by black") << d  << ChSquare(6,4) << ChSquares();
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(6,4), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(5,4), _data.pawn(CH_WHITE_COLOR));

        QTest::newRow("pawn e7 blocked by white") << d  << ChSquare(6, 4) << ChSquares();
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(6,4), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(5,4), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(5,3), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(5,5), _data.pawn(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(5,3));
        moves.push_back(ChSquare(5,5));

        QTest::newRow("pawn e7 blocked by white + 2 whites on diag") << d << ChSquare(6,4) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(6,4), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(5,4), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(5,3), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(5,5), _data.pawn(CH_BLACK_COLOR));

        QTest::newRow("pawn e7 blocked by black + 2 blackss on diag") << d
            << ChSquare(6,4) << ChSquares();
    }
    {
        ChPiecesTestData d;
        d.insert(ChSquare(4,4), _data.king(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(3, 4));
        moves.push_back(ChSquare(5, 4));
        moves.push_back(ChSquare(3, 3));
        moves.push_back(ChSquare(4, 3));
        moves.push_back(ChSquare(5, 3));
        moves.push_back(ChSquare(3, 5));
        moves.push_back(ChSquare(4, 5));
        moves.push_back(ChSquare(5, 5));

        QTest::newRow("king e3") << d  << ChSquare(4,4) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(4,4), _data.king(CH_WHITE_COLOR));
        d.insert(ChSquare(3,4), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(5,4), _data.pawn(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(5, 4));
        moves.push_back(ChSquare(3, 3));
        moves.push_back(ChSquare(4, 3));
        moves.push_back(ChSquare(5, 3));
        moves.push_back(ChSquare(3, 5));
        moves.push_back(ChSquare(4, 5));
        moves.push_back(ChSquare(5, 5));

        QTest::newRow("king e3 + 1 black + 1 white") << d  << ChSquare(4,4) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(0, 0), _data.king(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(0, 1));
        moves.push_back(ChSquare(1, 0));
        moves.push_back(ChSquare(1, 1));

        QTest::newRow("king a1") << d  << ChSquare(0, 0) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(0, 7), _data.king(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(0, 6));
        moves.push_back(ChSquare(1, 7));
        moves.push_back(ChSquare(1, 6));

        QTest::newRow("king h1") << d  << ChSquare(0, 7) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(7, 7), _data.king(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(7, 6));
        moves.push_back(ChSquare(6, 6));
        moves.push_back(ChSquare(6, 7));

        QTest::newRow("king h8") << d  << ChSquare(7, 7) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(7, 0), _data.king(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(7, 1));
        moves.push_back(ChSquare(6, 1));
        moves.push_back(ChSquare(6, 0));

        QTest::newRow("king a8") << d  << ChSquare(7, 0) << moves;
    }
    {
        ChPiecesTestData d;
        d.insert(ChSquare(3,4), _data.rook(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(3, 3));
        moves.push_back(ChSquare(3, 2));
        moves.push_back(ChSquare(3, 1));
        moves.push_back(ChSquare(3, 0));
        moves.push_back(ChSquare(3, 5));
        moves.push_back(ChSquare(3, 6));
        moves.push_back(ChSquare(3, 7));
        moves.push_back(ChSquare(2, 4));
        moves.push_back(ChSquare(1, 4));
        moves.push_back(ChSquare(0, 4));
        moves.push_back(ChSquare(4, 4));
        moves.push_back(ChSquare(5, 4));
        moves.push_back(ChSquare(6, 4));
        moves.push_back(ChSquare(7, 4));

        QTest::newRow("rook e4") << d  << ChSquare(3,4) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(3,4), _data.rook(CH_WHITE_COLOR));
        d.insert(ChSquare(3,3), _data.rook(CH_WHITE_COLOR));
        d.insert(ChSquare(3,2), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(3,5), _data.rook(CH_BLACK_COLOR));
        d.insert(ChSquare(3,7), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(2,4), _data.rook(CH_BLACK_COLOR));
        d.insert(ChSquare(1,4), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(4,4), _data.rook(CH_BLACK_COLOR));
        d.insert(ChSquare(5,4), _data.pawn(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(3, 5));
        moves.push_back(ChSquare(2, 4));
        moves.push_back(ChSquare(4, 4));

        QTest::newRow("rook e4 pieces around") << d  << ChSquare(3,4) << moves;
    }
    {
        ChPiecesTestData d;
        d.insert(ChSquare(3,4), _data.bishop(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(4, 5));
        moves.push_back(ChSquare(5, 6));
        moves.push_back(ChSquare(6, 7));
        moves.push_back(ChSquare(2, 3));
        moves.push_back(ChSquare(1, 2));
        moves.push_back(ChSquare(0, 1));
        moves.push_back(ChSquare(2, 5));
        moves.push_back(ChSquare(1, 6));
        moves.push_back(ChSquare(0, 7));
        moves.push_back(ChSquare(4, 3));
        moves.push_back(ChSquare(5, 2));
        moves.push_back(ChSquare(6, 1));
        moves.push_back(ChSquare(7, 0));

        QTest::newRow("bishop e4") << d  << ChSquare(3,4) << moves;
    }
    {
        ChPiecesTestData d;
        d.insert(ChSquare(6,1), _data.bishop(CH_WHITE_COLOR));
        d.insert(ChSquare(7,0), _data.bishop(CH_BLACK_COLOR));
        d.insert(ChSquare(7,2), _data.knight(CH_BLACK_COLOR));
        d.insert(ChSquare(5,2), _data.king(CH_WHITE_COLOR));
        d.insert(ChSquare(5,0), _data.pawn(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(7, 0));
        moves.push_back(ChSquare(7, 2));

        QTest::newRow("bishop b7 pieces around") << d  << ChSquare(6,1) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(5, 3), _data.queen(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(4, 3));
        moves.push_back(ChSquare(3, 3));
        moves.push_back(ChSquare(2, 3));
        moves.push_back(ChSquare(1, 3));
        moves.push_back(ChSquare(0, 3));
        moves.push_back(ChSquare(6, 3));
        moves.push_back(ChSquare(7, 3));
        moves.push_back(ChSquare(5, 2));
        moves.push_back(ChSquare(5, 1));
        moves.push_back(ChSquare(5, 0));
        moves.push_back(ChSquare(5, 4));
        moves.push_back(ChSquare(5, 5));
        moves.push_back(ChSquare(5, 6));
        moves.push_back(ChSquare(5, 7));
        moves.push_back(ChSquare(4, 2));
        moves.push_back(ChSquare(3, 1));
        moves.push_back(ChSquare(2, 0));
        moves.push_back(ChSquare(6, 4));
        moves.push_back(ChSquare(7, 5));
        moves.push_back(ChSquare(6, 2));
        moves.push_back(ChSquare(7, 1));
        moves.push_back(ChSquare(4, 4));
        moves.push_back(ChSquare(3, 5));
        moves.push_back(ChSquare(2, 6));
        moves.push_back(ChSquare(1, 7));

        QTest::newRow("queen d6") << d  << ChSquare(5, 3) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(7, 6), _data.queen(CH_BLACK_COLOR));
        d.insert(ChSquare(7, 7), _data.knight(CH_WHITE_COLOR));
        d.insert(ChSquare(6, 7), _data.bishop(CH_BLACK_COLOR));
        d.insert(ChSquare(6, 6), _data.bishop(CH_WHITE_COLOR));
        d.insert(ChSquare(6, 5), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(7, 4), _data.queen(CH_WHITE_COLOR));
        d.insert(ChSquare(7, 3), _data.pawn(CH_WHITE_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(7, 7));
        moves.push_back(ChSquare(6, 6));
        moves.push_back(ChSquare(7, 5));
        moves.push_back(ChSquare(7, 4));

        QTest::newRow("queen g8 pieces around") << d  << ChSquare(7, 6) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(5, 3), _data.knight(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(7, 2));
        moves.push_back(ChSquare(7, 4));
        moves.push_back(ChSquare(6, 1));
        moves.push_back(ChSquare(6, 5));
        moves.push_back(ChSquare(4, 1));
        moves.push_back(ChSquare(4, 5));
        moves.push_back(ChSquare(3, 2));
        moves.push_back(ChSquare(3, 4));

        QTest::newRow("knight d6") << d  << ChSquare(5, 3) << moves;
    }

    {
        ChPiecesTestData d;
        d.insert(ChSquare(1, 2), _data.knight(CH_BLACK_COLOR));
        d.insert(ChSquare(1, 3), _data.knight(CH_BLACK_COLOR));
        d.insert(ChSquare(3, 1), _data.bishop(CH_WHITE_COLOR));
        d.insert(ChSquare(3, 3), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(2, 4), _data.pawn(CH_BLACK_COLOR));
        d.insert(ChSquare(2, 0), _data.pawn(CH_WHITE_COLOR));
        d.insert(ChSquare(0, 0), _data.queen(CH_WHITE_COLOR));
        d.insert(ChSquare(0, 4), _data.knight(CH_BLACK_COLOR));
        d.insert(ChSquare(0, 3), _data.pawn(CH_BLACK_COLOR));

        ChSquares moves;
        moves.push_back(ChSquare(3, 1));
        moves.push_back(ChSquare(0, 0));
        moves.push_back(ChSquare(2, 0));

        QTest::newRow("knight c2 pieces around") << d  << ChSquare(1, 2) << moves;
    }
}

void ChPiecesTest::testCasePiece()
{
    QFETCH(ChPiecesTestData, position);
    QFETCH(ChSquare, pieceToMove);
    QFETCH(ChSquares, moves);

    initData(position);
    ChSquares result = _data.at(pieceToMove)->moves(pieceToMove, &_data);
    std::sort(result.begin(), result.end());
    std::sort(moves.begin(), moves.end());

    QCOMPARE(result, moves);
}

void ChPiecesTest::testCasePawnIncorrect()
{
    _data.clear();
    _data.add(ChSquare(0,1), _data.pawn(CH_WHITE_COLOR));
    QVERIFY_EXCEPTION_THROWN(_data.pawn(CH_WHITE_COLOR)->moves(ChSquare(0,1), &_data),
        ChLogicException);
    _data.add(ChSquare(7,3), _data.pawn(CH_BLACK_COLOR));
    QVERIFY_EXCEPTION_THROWN(_data.pawn(CH_BLACK_COLOR)->moves(ChSquare(7,3), &_data),
        ChLogicException);
    _data.add(ChSquare(6,3), _data.pawn(CH_BLACK_COLOR));
    QVERIFY_EXCEPTION_THROWN(_data.pawn(CH_WHITE_COLOR)->moves(ChSquare(6,3), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.pawn(CH_WHITE_COLOR)->moves(ChSquare(1,3), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.king(CH_WHITE_COLOR)->moves(ChSquare(6,3), &_data),
        ChLogicException);
}

void ChPiecesTest::testCaseKingIncorrect()
{
    _data.clear();
    _data.add(ChSquare(2,1), _data.king(CH_WHITE_COLOR));
    QVERIFY_EXCEPTION_THROWN(_data.pawn(CH_WHITE_COLOR)->moves(ChSquare(2,1), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.king(CH_WHITE_COLOR)->moves(ChSquare(1,3), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.king(CH_BLACK_COLOR)->moves(ChSquare(2,1), &_data),
        ChLogicException);
}

void ChPiecesTest::testCaseRookIncorrect()
{
    _data.clear();
    _data.add(ChSquare(2,1), _data.rook(CH_WHITE_COLOR));
    QVERIFY_EXCEPTION_THROWN(_data.pawn(CH_WHITE_COLOR)->moves(ChSquare(2,1), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.rook(CH_WHITE_COLOR)->moves(ChSquare(1,3), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.rook(CH_BLACK_COLOR)->moves(ChSquare(2,1), &_data),
        ChLogicException);
}

void ChPiecesTest::testCaseBishopIncorrect()
{
    _data.clear();
    _data.add(ChSquare(2,1), _data.bishop(CH_WHITE_COLOR));
    QVERIFY_EXCEPTION_THROWN(_data.pawn(CH_WHITE_COLOR)->moves(ChSquare(2,1), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.bishop(CH_WHITE_COLOR)->moves(ChSquare(1,3), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.bishop(CH_BLACK_COLOR)->moves(ChSquare(2,1), &_data),
    ChLogicException);
}

void ChPiecesTest::testCaseQueenIncorrect()
{
    _data.clear();
    _data.add(ChSquare(2,1), _data.queen(CH_WHITE_COLOR));
    QVERIFY_EXCEPTION_THROWN(_data.pawn(CH_WHITE_COLOR)->moves(ChSquare(2,1), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.queen(CH_WHITE_COLOR)->moves(ChSquare(1,3), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.queen(CH_BLACK_COLOR)->moves(ChSquare(2,1), &_data),
    ChLogicException);
}

void ChPiecesTest::testCaseKnightIncorrect()
{
    _data.clear();
    _data.add(ChSquare(2,1), _data.knight(CH_WHITE_COLOR));
    QVERIFY_EXCEPTION_THROWN(_data.pawn(CH_WHITE_COLOR)->moves(ChSquare(2,1), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.knight(CH_WHITE_COLOR)->moves(ChSquare(1,3), &_data),
        ChLogicException);
    QVERIFY_EXCEPTION_THROWN(_data.knight(CH_BLACK_COLOR)->moves(ChSquare(2,1), &_data),
    ChLogicException);
}

void ChPiecesTest::initData(const ChPiecesTestData &d)
{
    _data.clear();

    for (ChPiecesTestData::const_iterator it = d.begin(); it != d.end(); ++it) {
        _data.add(it.key(), it.value());
    }
}

QTEST_APPLESS_MAIN(ChPiecesTest)

#include "tst_chpiecestest.moc"
