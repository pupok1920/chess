import QtQuick 2.0
import QtQuick.Controls 1.3

GridView {
    property string squareColorWhite: "white"
    property string squareColorWhiteSelected: "deepskyblue"
    property string squareColorWhiteHighlighted: "lightsteelblue"
    property string squareColorBlack: "brown"
    property string squareColorBlackSelected: "dodgerblue"
    property string squareColorBlackHighlighted: "steelblue"

    width: 480
    height: 480
    cellWidth: 60
    cellHeight: 60

    verticalLayoutDirection: GridView.BottomToTop
    Component {
        id: boardDelegate
        Rectangle {
            id: squareRect
            width: 60
            height: 60
            Image {
                id: piece
                source: {
                    if (cell_item_type != "") {
                        "qrc:/images/" + cell_item_type + "_" +  cell_item_color + ".png"
                    }
                    else {
                        ""
                    }
                }
            }
            border.color: "cyan"
            border.width: (cell_move_indication == true) ? 2 : 0
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var x = index % 8;
                    var y = Math.floor(index/8);
                    boardModel.onSquareClicked(index);
                }
            }
            states: [
                State {
                    name: "NORMAL"
                    when: (!cell_item_selected) && (!cell_highlighted)
                    PropertyChanges {
                        target: squareRect
                        color: (cell_color == "white") ? squareColorWhite : squareColorBlack
                    }
                },
                State {
                    name: "SELECTED"
                    when: cell_item_selected
                    PropertyChanges {
                        target: squareRect
                        color: (cell_color == "white") ? squareColorWhiteSelected : squareColorBlackSelected
                    }
                },
                State {
                    name: "HIGHLIGHTED"
                    when: cell_highlighted
                    PropertyChanges {
                        target: squareRect
                        color: (cell_color == "white") ? squareColorWhiteHighlighted : squareColorBlackHighlighted
                    }
                }
            ]
//            transitions: Transition {
//                ColorAnimation {}
//            }
        }
    }
    delegate: boardDelegate
    focus: true
    interactive: false
}
