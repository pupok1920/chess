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
            property bool activePlayer: boardModel.activePlayer

            Rectangle {
                id: indicRect
                width: 30
                height: 30
                border.color: "red"
                x: 145
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
    Button {
        id: homeButton
        text: "NTG6"
        tooltip: qsTr("home")
        x: 205
        y: 485
        onClicked: parent.homeClicked()
    }
    Button {
        id: redoButton
        text: "to NTG6"
        tooltip: qsTr("next")
        x: 300
        y: 485
        onClicked: parent.redoClicked()
    }
    Button {
        id: undoButton
        text: "from NTG6"
        tooltip: qsTr("prev")
        x: 385
        y: 485
        onClicked: parent.undoClicked()
    }
}
