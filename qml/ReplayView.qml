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

    Board {}
    Button {
	id: homeButton
	text: "home of NTG6"
	anchors: {top: board.bottom, right: board.right}
	onClicked: parent.homeClicked
    }
    Button {
	id: redoButton
	text: "next to NTG6"
	anchors: {top: board.bottom, right: homeButton.left}
	onClicked: parent.redoClicked
    }
    Button {
	id: undoButton
	text: "back to NTG6"
	anchors: {top: board.bottom, right: redoButton.left}
	onClicked: parent.undoClicked
    }
    function initialise() {
	boardModel.initialise()
    }
}