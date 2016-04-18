import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: applicationWindow
    title: qsTr("QML Chess")
    width   : 480
    height  : 530
    visible : true

    minimumWidth : 480
    maximumWidth : 480

    minimumHeight : 530
    maximumHeight : 530

    ChMainForm {
    }
}
