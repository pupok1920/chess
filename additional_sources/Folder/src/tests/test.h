#ifndef TEST_H
#define TEST_H

#include <QString>
#include <QtTest>
#include <QMap>

#include "chboarddata.h"
#include "chexception.h"

Q_DECLARE_METATYPE(ChPieces)
Q_DECLARE_METATYPE(ChSquares)
Q_DECLARE_METATYPE(ChSquare)

typedef QMap<ChSquare, const ChPiece *> ChPiecesTestData;

Q_DECLARE_METATYPE(ChPiecesTestData)

#endif // TEST_H

