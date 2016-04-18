#ifndef CHSELECTION_H
#define CHSELECTION_H

#include "chlib.h"
#include "chsquare.h"

class QMLCHESSLIB_COMMON_DLLSPEC ChSelection
{
    Q_DECLARE_TR_FUNCTIONS(ChSelection)
public:
    ChSelection();
    ~ChSelection();
    bool isSelected(const ChSquare &square) const;
    void setSelected(const ChSquare &square);
    bool hasSelected() const;
    void clearSelected();
    const ChSquare &selected() const;

    bool isHighlighted(const ChSquare &square) const;
    void setHighlighted(const ChSquares &squares);
    const ChSquares &highlighted() const;

private:
    bool _hasSelected;
    ChSquare _selected;
    ChSquares _highlighted;
};

#endif // CHSELECTION_H
