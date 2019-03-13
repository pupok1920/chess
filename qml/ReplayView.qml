import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.5
import QtQml.Models 2.2
import QtQuick.Dialogs 1.1
import Qt.labs.settings 1.0

Item {
    signal homeClicked
    signal redoClicked
    signal undoClicked

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
                }
            }
        }

        Item {
            id: indicItem
            x: 20
            y: 485
            property int activePlayer: boardModel.activePlayer

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
                text: "'s move"
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
                },
                State {
                    name: "BLACKMOVE"
                    when: indicItem.activePlayer === indicItem.blackColor
                    PropertyChanges {
                        target: indicRect; color: "black"
                    }
                }
            ]
        }
    }
    Button {
        id: homeButton
        text: "Home"
        tooltip: qsTr("home")
        x: 205
        y: 485
        onClicked: parent.homeClicked()
    }
    Button {
        id: undoButton
        text: "Prev"
        tooltip: qsTr("prev")
        x: 300
        y: 485
        onClicked: parent.undoClicked()
    }
    Button {
        id: redoButton
        text: "Next"
        tooltip: qsTr("next")
        x: 385
        y: 485
        onClicked: parent.redoClicked()
    }
}
