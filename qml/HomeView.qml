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
        anchors.left: startUpImage.left
        anchors.leftMargin: 30
        y: 486
        //iconSource:
        onClicked: parent.playClicked()
    }
    Button {
        id: loadButton
        text: "Load Game"
        tooltip: qsTr("load")
        anchors.right: startUpImage.right
        anchors.rightMargin: 30
        y: 486
        //iconSource:
        onClicked: parent.loadClicked()
    }
    function initialise() {
        boardModel.clear()
    }
}
