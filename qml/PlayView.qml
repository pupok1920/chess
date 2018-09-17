import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.5
import QtQml.Models 2.2
import QtQuick.Dialogs 1.1
import Qt.labs.settings 1.0

Item {
    signal saveClicked
    signal stopClicked

    Board {
        id: board
    }
    Button {
        id: saveButton
        text: "Save Game"
        tooltip: qsTr("save")
        x: 220
        y: 485
        onClicked: parent.saveClicked()
    }
    Button {
        id: stopButton
        text: "Home"
        tooltip: qsTr("home")
        x: 340
        y: 485
        onClicked: parent.stopClicked()
    }
    function initialise() {
        boardModel.initialise()
    }
}

