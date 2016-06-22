import QtQuick 2.5
import QtQuick.Controls 1.3

Item {
    signal playClicked
    signal loadClicked

    Rectangle {
        id: startUpImage
        width: 480
        height: 480
        color: "black"

        /*Image {
            source:
        }*/
    }

    Button {
        id: playButton
        text: "connect.."
        tooltip: qsTr("play")
        x: 40
        y: 485
        //anchors.top: startUpImage.bottom
        //anchors.left: loadButton.left
        //iconSource:
        onClicked: parent.playClicked()
    }
    Button {
        id: loadButton
        text: "log.."
        tooltip: qsTr("load")
        x: 140
        y: 485
        //anchors.top: startUpImage.bottom
        //anchors.left: startUpImage.right
        //iconSource:
        onClicked: parent.loadClicked()
    }
}
