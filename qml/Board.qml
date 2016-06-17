import QtQuick 2.0

Item {

    Image {
        id: board
        anchors.fill: parent
        //source: "qrc:/assets/board.jpg"
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
                    if(item_type != "") {
                        "qrc:/assets/" + item_type + "_" + item_color + ".png"
                    }
                    else {""}
                }
                anchors.centerIn: parent
                //smooth: true
                //fillMode: Image.PreserveAspectFit
            }

            states: [
                State {
                    name: "inDrag"
                    when: index == view.draggedFrom
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
        x: 15
        y: 485
        property bool activePlayer: boardModel.activePlayer

        Rectangle {
            id: indicRect
            width: 30
            height: 30
            border.color: "red"
            x: 140
        }
        Text {
            id: indicText
            font.family: "Helvetica"
            font.pointSize: 12
            color: "black"
            y: 5
        }

        states: [
            State {
                name: "WHITEMOVE"
                when: indicItem.activePlayer == true
                PropertyChanges {
                    target: indicRect; color: "white"
                }
                PropertyChanges {
                    target: indicText; text: "waiting for NTG6..."
                }
            },
            State {
                name: "BLACKMOVE"
                when: indicItem.activePlayer == false
                PropertyChanges {
                    target: indicRect; color: "black"
                }
                PropertyChanges {
                    target: indicText; text: "connecting if1moc..."
                }
            }
        ]
    }

}

