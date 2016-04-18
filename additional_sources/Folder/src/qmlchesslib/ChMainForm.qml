import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Item {
    property var homeViewForm: ChHomeView {
        id: homeView
    }
    property var playViewForm: ChPlayView {
        id: playView
    }
    property var replayViewForm: ChReplayView {
        id: replayView
    }
    FileDialog {
        id: saveFileDialog
        title: qsTr("Please choose a file")
        selectExisting: false
        selectMultiple: false
        nameFilters: [ qsTr("XML files (*.xml)"), qsTr("All files (*)") ]
        onAccepted: {
            boardModel.save(saveFileDialog.fileUrl)
        }
    }
    FileDialog {
        id: loadFileDialog
        title: qsTr("Please choose a file to open")
        selectExisting: true
        selectMultiple: false
        nameFilters: [ qsTr("XML files (*.xml)"), qsTr("All files (*)") ]
        onAccepted: {
            if (boardModel.load(loadFileDialog.fileUrl)) {
                stackView.pop()
                stackView.push(replayViewForm)
            }
        }
    }
    MessageDialog {
        id: alertDialog
        title: qsTr("Alert")
    }
    StackView {
        id: stackView
        initialItem: homeViewForm
        delegate: StackViewDelegate {
            function transitionFinished(properties)
            {
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
        onStartClicked: {
            stackView.push(playViewForm)
            playView.initialize()
        }
        onLoadClicked: {
            loadFileDialog.visible = true
        }
    }
    Connections {
        target: playView
        onStopClicked: {
            stackView.pop()
            homeView.initialize()
        }
        onSaveClicked: {
            saveFileDialog.visible = true
        }
    }
    Connections {
        target: replayView
        onStartClicked: {
            stackView.push({ item: playViewForm, replace: true })
            playView.initialize()
        }
        onLoadClicked: {
            loadFileDialog.visible = true
        }
        onRedoClicked: {
            boardModel.redo()
        }
        onUndoClicked: {
            boardModel.undo()
        }
    }
    Connections {
        target: boardModel
        onAlert: {
            alertDialog.text = description
            alertDialog.open()
        }
    }
}
