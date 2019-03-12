import QtQuick 2.0

Item {

    Image {
        id: boardImage
        source: "qrc:/assets/board.png"
    }

    GridView {
        id: view
        width: 480
        height: 480
        cellWidth: 60
        cellHeight: 60
        model: boardModel
        delegate: dndDelegate
        interactive: false
        //verticalLayoutDirection: GridView.BottomToTop

        property int draggedFrom: -1
        property int draggedTo: -1

        Item {
            id: dndContainer
            anchors.fill: parent
        }

        MouseArea {
            id: coords
            anchors.fill: parent

            onPressed: {
                view.draggedFrom = view.indexAt(mouseX, mouseY)
            }

            onReleased: {
                view.draggedTo = view.indexAt(mouseX, mouseY)
                if (view.draggedFrom !== view.draggedTo) {
                    boardModel.move(view.draggedFrom, view.draggedTo)
                }
                view.draggedFrom = -1
            }
        }
    }

    Component {
        id: dndDelegate
        Item {
            id: wrapper
            width: view.cellWidth
            height: view.cellHeight
            Image {
                id: itemImage
                source: {
                    if(item_type !== "") {
                        "qrc:/assets/" + item_type + "_" + item_color + ".png"
                    }
                    else {""}
                }
                anchors.centerIn: parent
            }

            states: [
                State {
                    name: "inDrag"
                    when: index === view.draggedFrom
                    PropertyChanges {
                        target: itemImage; parent: dndContainer
                    }
                    PropertyChanges {
                        target: itemImage; anchors.centerIn: undefined
                    }
                    PropertyChanges {
                        target: itemImage; x: coords.mouseX - itemImage.width / 2
                    }
                    PropertyChanges {
                        target: itemImage; y: coords.mouseY - itemImage.height / 2
                    }
                }
           ]
        }
    }

    Item {
        id: indicItem
        x: 20
        y: 485
        property int activePlayer: boardModel.activePlayer
        property int playerColor: boardModel.playerColor

        property int whiteColor: 0
        property int blackColor: 1

        Rectangle {
            id: indicRect
            width: 30
            height: 30
            border.color: "red"
        }
        Text {
            id: indicText
            font.family: "Helvetica"
            font.pointSize: 16
            color: "black"
            x: 35
            y: 5
        }

        states: [
            State {
                name: "WHITEMOVE"
                when: indicItem.activePlayer === indicItem.whiteColor
                PropertyChanges {
                  target: indicRect; color: "white"
                }
                PropertyChanges {
                  target: indicText; text: if(indicItem.activePlayer === indicItem.playerColor) {
                    "your move"
                  }
                  else { "enemy's move"}
                }
            },
            State {
                name: "BLACKMOVE"
                when: indicItem.activePlayer === indicItem.blackColor
                PropertyChanges {
                  target: indicRect; color: "black"
                }
                PropertyChanges {
                  target: indicText; text: if(indicItem.activePlayer === indicItem.playerColor) {
                    "your move"
                  }
                  else { "enemy's move"}
                }
            }
        ]
    }

}

