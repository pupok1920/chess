import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    signal stopClicked
    signal saveClicked
    ChBoard {
        id: board
        model: boardModel
        anchors { top: parent.top; bottom: stopButton.top }
    }
    Button {
        id: stopButton
        anchors { top: board.bottom; right: loadButton.left }
        tooltip: qsTr("Stop")
        iconSource: "qrc:/images/stop.png"
        onClicked: parent.stopClicked()
    }
    Button {
        id: loadButton
        anchors { top: board.bottom; right: board.right }
        tooltip: qsTr("Save")
        iconSource: "qrc:/images/save_as.png"
        onClicked: parent.saveClicked()
    }

    function initialize() {
        boardModel.initialize()
    }
}

