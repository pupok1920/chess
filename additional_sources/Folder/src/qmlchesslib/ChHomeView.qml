import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    signal startClicked
    signal loadClicked

    ChBoard {
        id: board
        model: boardModel
        squareColorBlack: "black"
        anchors { top: parent.top; bottom: startButton.top }
    }
    Button {
        id: startButton
        anchors { top: board.bottom; right: loadButton.left }
        tooltip: qsTr("Start")
        iconSource: "qrc:/images/start.png"
        onClicked: parent.startClicked()
    }
    Button {
        id: loadButton
        anchors { top: board.bottom; right: board.right }
        tooltip: qsTr("Load")
        iconSource: "qrc:/images/folder.png"
        onClicked: parent.loadClicked()
    }
    function initialize() {
        boardModel.clear()
    }
}

