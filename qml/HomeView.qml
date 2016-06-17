import QtQuick 2.5
import QtQuick.Controls 1.3

Item {
    signal playClicked
    signal loadClicked

    Rectangle {
	width: 480
	height: 480
	color: "white"

	/*Image {
	    source:
	}*/
    }

    Button {
	id: playButton
	text: "connect.."
	tooltip: qsTr("play")
	//iconSource: 
	onClicked: parent.playClicked()
    }
    Button {
	id: loadButton
	text: "log.."
	tooltip: qsTr("load")
	//iconSource: 
	onClicked: parent.loadClicked()
    }
}