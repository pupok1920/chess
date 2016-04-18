#ifndef CHPLAYER_H
#define CHPLAYER_H

#include <QObject>

#include "chlib.h"
#include "chsquare.h"

class ChBoardData;

class QMLCHESSLIB_COMMON_DLLSPEC ChPlayer: public QObject
{
    Q_OBJECT
public:
    virtual ~ChPlayer();

    virtual void setBoardData(const ChBoardData *boardData) = 0;
    virtual void startMove() = 0;
    virtual void stopMove() = 0;

signals:
    void moved(int from, int to);
    void selectionChanged(int selected, const ChSquares &highlighted);
};

#endif // CHPLAYER_H
