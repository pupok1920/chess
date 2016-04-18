import QtQuick 2.0
import QtQuick.Controls 1.3

Button {
    property string enabledImageSource: ""
    property string disabledImageSource: ""
    id: buttonId
    states: [
        State {
            name: "ENABLED"
            when: buttonId.enabled
            PropertyChanges {
                target: buttonId
                iconSource: enabledImageSource
            }
        },
        State {
            name: "DISABLED"
            when: !buttonId.enabled
            PropertyChanges {
                target: buttonId
                iconSource: disabledImageSource
            }
        }
    ]

}

