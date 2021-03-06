import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.5
import QtQml.Models 2.2
import QtQuick.Dialogs 1.1
import Qt.labs.settings 1.0

ApplicationWindow {
    id: applicationWindow
    title: qsTr("Chess")
    //width   : field.width
    //height  : field.height
    visible : true
    color: "#A9AEA9"

    minimumWidth : 480
    maximumWidth : 480

    minimumHeight : 520
    maximumHeight : 520

    Item {
        id: mainContainer

        property var homeViewForm: HomeView {
            id: homeView
        }
        property var playViewForm: PlayView {
            id: playView
        }
        property var replayViewForm: ReplayView {
            id: replayView
        }

        FileDialog {
            id: saveFileDialog
            title: "Please make your choose for save Game data"
            selectExisting: false
            selectFolder: false
            selectMultiple: false
            nameFilters: [ qsTr("TXT files (*.txt)"), qsTr("All files (*)") ]
            onAccepted: {
                boardModel.save(saveFileDialog.fileUrl)
                stackView.push({ item: mainContainer.homeViewForm, replace: true})
                homeView.initialise()
            }
        }
        FileDialog {
            id: loadFileDialog
            title: "Please make your choose for load Game data"
            selectExisting: true
            selectFolder: false
            selectMultiple: false
            nameFilters: [ qsTr("TXT files (*.txt)"), qsTr("All files (*)") ]
            onAccepted: {
                boardModel.load(loadFileDialog.fileUrl)
            }
            onRejected: {
                stackView.push({ item: mainContainer.homeViewForm, replace: true})
            }
        }

        StackView {
        id: stackView
        initialItem: parent.homeViewForm
  	    delegate: StackViewDelegate {
            function transitionFinished(properties) {
                properties.exitItem.opacity = 1
            }

            pushTransition: StackViewTransition {
                PropertyAnimation {
                    target: enterItem
                    property: "opacity"
                    from: 0
                    to: 1
                }
                PropertyAnimation {
                    target: exitItem
                    property: "opacity"
                    from: 1
                    to: 0
                }
            }
	    }
	}

        Connections {
            target: homeView
            onPlayClicked: {
                stackView.push(mainContainer.playViewForm)
                playView.initialise()
            }
            onLoadClicked: {
                loadFileDialog.open()
                stackView.pop()
                stackView.push(mainContainer.replayViewForm)
            }
        }
        Connections {
            target: playView
            onStopClicked: {
                stackView.pop()
                homeView.initialise()
            }
            onSaveClicked: {
                saveFileDialog.open()
            }
        }
        Connections {
            target: replayView
            onHomeClicked: {
                stackView.push({ item: mainContainer.homeViewForm, replace: true})
                homeView.initialise()
            }
            onRedoClicked: {
                boardModel.redo()
            }
            onUndoClicked: {
                boardModel.undo()
            }
        }
    }
}





































