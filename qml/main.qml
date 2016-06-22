import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.5
import QtQml.Models 2.2
import QtQuick.Dialogs 1.1
import Qt.labs.settings 1.0

ApplicationWindow {
    id: applicationWindow
    title: qsTr("NTG6: static_linking")
    //width   : field.width
    //height  : field.height
    visible : true

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
            title: "Please make your choose for save NTG6 data"

            onAccepted: {
                boardModel.save(saveFileDialog.fileUrl)
            }
        }
        FileDialog {
            id: loadFileDialog
            title: "Please make your choose for load NTG6 data"

            onAccepted: {
                boardModel.load(loadFileDialog.fileUrl)
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
            }
        }
        Connections {
            target: playView
            onStopClicked: {
                stackView.pop()
                //homeView.initialise()
            }
            onSaveClicked: {
                saveFileDialog.visible = true
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





































