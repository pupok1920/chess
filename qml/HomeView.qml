import QtQuick 2.5
import QtQuick.Controls 1.3

Item {
    signal playClicked
    signal loadClicked

    Rectangle {
        id: startUpImage
        width: 480
        height: 480
        //color: "black"

        Image {
          source: "qrc:/assets/start.jpg"
        }
    }

    Button {
        id: playButton
        text: "Play"
        tooltip: qsTr("play")
        x: 40
        y: 485
        //iconSource:
        onClicked: parent.playClicked()
    }
    Button {
        id: loadButton
        text: "Load Game"
        tooltip: qsTr("load")
        x: 140
        y: 485
        //iconSource:
        onClicked: parent.loadClicked()
    }
    function initialise() {
        boardModel.clear()
    }
}
