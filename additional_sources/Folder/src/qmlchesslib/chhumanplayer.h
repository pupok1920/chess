#ifndef CHHUMANPLAYER_H
#define CHHUMANPLAYER_H

#include "chlib.h"
#include "chplayer.h"

class ChValidator;

class QMLCHESSLIB_COMMON_DLLSPEC ChHumanPlayer : public ChPlayer
{
    Q_OBJECT
public:
    explicit ChHumanPlayer(ChPieceColor color);
    ~ChHumanPlayer();

    void setBoardData(const ChBoardData *boardData);
    void startMove();
    void stopMove();
    void setValidator(const ChValidator* validator);

public slots:
    void onSquareClicked(int index, int selected, const ChSquares &highlighted);

private:
    void move(const ChSquare &from, const ChSquare &to);

private:
    Q_DISABLE_COPY(ChHumanPlayer)
    const ChBoardData *_data;
    bool _inMove;
    const ChValidator *_validator;
    ChPieceColor _color;
};

#endif // CHHUMANPLAYER_H
