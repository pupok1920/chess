import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.5
import QtQml.Models 2.2
import Qt.labs.controls 1.0
import QtQuick.Dialogs 1.1

ApplicationWindow {
    id: applicationWindow
    title: qsTr("QML Chess")
    width   : field.width
    height  : field.height
    visible : true

    minimumWidth : 480
    maximumWidth : 480

    minimumHeight : 520
    maximumHeight : 520

    /*Rectangle {
        id: resetButton
        width: 100; height: 40
        radius: 7
        x: 190
        y: 480
        color: "#7b917b"

        Text {
            text: "Reset"
            anchors.centerIn: parent
            font.family: "Helvetica"
            font.pointSize: 24
        }

        MouseArea {
             anchors.fill: parent
             onClicked:  resetButton.color = "red"
        }

    }*/

    Item {
      id: field

      width: 480
      height: 480

      Image {
          id: board
          anchors.fill: parent
          source: "src/board.jpg"
      }

      Component {
          id: dndDelegate
          Item {
              id: wrapper
              width: view.cellWidth
              height: view.cellHeight
              Image {
                  id: itemImage
                  source: item_source
                  anchors.centerIn: parent
                  smooth: true
                  fillMode: Image.PreserveAspectFit
              }

              states: [
                  State {
                      name: "inDrag"
                      when: index == view.draggedItemIndex
                      PropertyChanges {
                          target: itemImage; parent: dndContainer
                      }
                      PropertyChanges {
                          target: itemImage; anchors.centerIn: undefined
                      }
                      PropertyChanges {
                          target: itemImage; x: coords.mouseX - itemImage.width / 2
                      }
                      PropertyChanges {
                          target: itemImage; y: coords.mouseY - itemImage.height / 2
                      }
                  }
              ]
          }
      }

/*      ListModel {
          id: dataModel

          ListElement {
              indx: 1
              source: "src/rook_black.png"
          }
          ListElement {
              indx: 2
              source: "src/knight_black.png"
          }
          ListElement {
              indx: 3
              source: "src/bishop_black.png"
          }
          ListElement {
              indx: 4
              source: "src/queen_black.png"
          }
          ListElement {
              indx: 5
              source: "src/king_black.png"
          }
          ListElement {
              indx: 6
              source: "src/bishop_black.png"
          }
          ListElement {
              indx: 7
              source: "src/knight_black.png"
          }
          ListElement {
              indx: 8
              source: "src/rook_black.png"
          }
          ListElement {
              indx: 9
              source: "src/pawn_black.png"
          }
          ListElement {
              indx: 10
              source: "src/pawn_black.png"
          }
          ListElement {
              indx: 11
              source: "src/pawn_black.png"
          }
          ListElement {
              indx: 12
              source: "src/pawn_black.png"
          }
          ListElement {
              indx: 13
              source: "src/pawn_black.png"
          }
          ListElement {
              indx: 14
              source: "src/pawn_black.png"
          }
          ListElement {
              indx: 15
              source: "src/pawn_black.png"
          }
          ListElement {
              indx: 16
              source: "src/pawn_black.png"
          }

          ListElement {
              indx: 17
              source: ""
          }
          ListElement {
              indx: 18
              source: ""
          }
          ListElement {
              indx: 19
              source: ""
          }
          ListElement {
              indx: 20
              source: ""
          }
          ListElement {
              indx: 21
              source: ""
          }
          ListElement {
              indx: 22
              source: ""
          }
          ListElement {
              indx: 23
              source: ""
          }
          ListElement {
              indx: 24
              source: ""
          }
          ListElement {
              indx: 25
              source: ""
          }
          ListElement {
              indx: 26
              source: ""
          }
          ListElement {
              indx: 27
              source: ""
          }
          ListElement {
              indx: 28
              source: ""
          }
          ListElement {
              indx: 29
              source: ""
          }
          ListElement {
              indx: 30
              source: ""
          }
          ListElement {
              indx: 31
              source: ""
          }
          ListElement {
              indx: 32
              source: ""
          }
          ListElement {
              indx: 33
              source: ""
          }
          ListElement {
              indx: 34
              source: ""
          }
          ListElement {
              indx: 35
              source: ""
          }
          ListElement {
              indx: 36
              source: ""
          }
          ListElement {
              indx: 37
              source: ""
          }
          ListElement {
              indx: 38
              source: ""
          }
          ListElement {
              indx: 39
              source: ""
          }
          ListElement {
              indx: 40
              source: ""
          }
          ListElement {
              indx: 41
              source: ""
          }
          ListElement {
              indx: 42
              source: ""
          }
          ListElement {
              indx: 43
              source: ""
          }
          ListElement {
              indx: 44
              source: ""
          }
          ListElement {
              indx: 45
              source: ""
          }
          ListElement {
              indx: 46
              source: ""
          }
          ListElement {
              indx: 47
              source: ""
          }
          ListElement {
              indx: 48
              source: ""
          }
          ListElement {
              indx: 49
              source: "src/pawn_white.png"
          }
          ListElement {
              indx: 50
              source: "src/pawn_white.png"
          }
          ListElement {
              indx: 51
              source: "src/pawn_white.png"
          }
          ListElement {
              indx: 52
              source: "src/pawn_white.png"
          }
          ListElement {
              indx: 53
              source: "src/pawn_white.png"
          }
          ListElement {
              indx: 54
              source: "src/pawn_white.png"
          }
          ListElement {
              indx: 55
              source: "src/pawn_white.png"
          }
          ListElement {
              indx: 56
              source: "src/pawn_white.png"
          }
          ListElement {
              indx: 57
              source: "src/rook_white.png"
          }
          ListElement {
              indx: 58
              source: "src/knight_white.png"
          }
          ListElement {
              indx: 59
              source: "src/bishop_white.png"
          }
          ListElement {
              indx: 60
              source: "src/queen_white.png"
          }
          ListElement {
              indx: 61
              source: "src/king_white.png"
          }
          ListElement {
              indx: 62
              source: "src/bishop_white.png"
          }
          ListElement {
              indx: 63
              source: "src/knight_white.png"
          }
          ListElement {
              indx: 64
              source: "src/rook_white.png"
          }
       }
*/
      GridView {
          id: view

          width: 480
          height: 480
          cellWidth: 60
          cellHeight: 60
          model: boardModel
          delegate: dndDelegate
          verticalLayoutDirection: GridView.BottomToTop

          property int draggedItemIndex: -1

          interactive: false

          Item {
              id: dndContainer
              anchors.fill: parent
          }

          MouseArea {
              id: coords
              anchors.fill: parent
              onReleased: {
                    if (view.draggedItemIndex != -1 &&
                            view.draggedItemIndex >= 0 &&
                            view.draggedItemIndex < view.count &&
                            view.draggedItemIndex != view.indexAt(mouseX, mouseY)
                            ) {
                        var sss = view.model.get(view.draggedItemIndex).source
                        view.model.set(view.indexAt(mouseX, mouseY), {"source":sss})
                        view.model.set(view.draggedItemIndex, {"source":""})
                    }
              }

              onPressed: {
                    view.draggedItemIndex = view.indexAt(mouseX, mouseY)
              }
          }
       }
    }
}





































