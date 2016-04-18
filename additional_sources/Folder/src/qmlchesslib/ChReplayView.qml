import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    signal startClicked
    signal loadClicked
    signal undoClicked
    signal redoClicked
    ChBoard {
        id: board
        model: boardModel
        squareColorWhite: "yellow"
        anchors { top: parent.top; bottom: startButton.top }
    }
    Button {
        id: startButton
        anchors { top: board.bottom; right: loadButton.left }
        tooltip: qsTr("Start")
        iconSource: "qrc:/images/start.png"
        onClicked: parent.startClicked()
    }
    ChButton {
        id: undoButton
        anchors { top: board.bottom; left: board.left }
        onClicked: parent.undoClicked()
        tooltip: qsTr("prev")
        enabled: boardModel.canUndo()
        enabledImageSource: "qrc:/images/arrow_left.png"
        disabledImageSource: "qrc:/images/arrow_left_disabled.png"
    }

    ChButton {
        id: redoButton
        anchors { top: board.bottom; left: undoButton.right }
        onClicked: parent.redoClicked()
        tooltip: qsTr("next")
        enabled: boardModel.canRedo()
        enabledImageSource: "qrc:/images/arrow_right.png"
        disabledImageSource: "qrc:/images/arrow_right_disabled.png"
    }

    Button {
        id: loadButton
        anchors { top: board.bottom; right: board.right }
        tooltip: qsTr("Load")
        iconSource: "qrc:/images/folder.png"
        onClicked: parent.loadClicked()
    } 

    Connections {
        target: boardModel
        onCanRedoChanged: {
            redoButton.enabled = boardModel.canRedo()
        }
        onCanUndoChanged: {
            undoButton.enabled = boardModel.canUndo()
        }
    }
}

