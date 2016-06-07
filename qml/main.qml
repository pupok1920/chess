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
    width   : field.width
    height  : field.height
    visible : true

    minimumWidth : 480
    maximumWidth : 480

    minimumHeight : 520
    maximumHeight : 520

    Item {
      id: field

      width: 480
      height: 480

      Image {
          id: board
          anchors.fill: parent
          //source: "qrc:/assets/board.jpg"
      }

      Item {
          id: indicItem
          x: 20
          y: 485
          property bool activePlayer: boardModel.activePlayer

          Rectangle {
              id: indicRect
              width: 30
              height: 30
              border.color: "red"
              x: 195
              //color: (boardModel.getActivePlayer()===0) ? "black" : "white"
          }
          Text {
              id: indicText
              //text: toString(boardModel.getActivePlayer())
              font.family: "Helvetica"
              font.pointSize: 12
              color: "black"
          }

          states: [
              State {
                  name: "WHITEMOVE"
                  when: indicItem.activePlayer == true
                  PropertyChanges {
                      target: indicRect; color: "white"
                  }
                  PropertyChanges {
                      target: indicText; text: "waiting for NTG6..."
                  }
              },
              State {
                  name: "BLACKMOVE"
                  when: indicItem.activePlayer == false
                  PropertyChanges {
                      target: indicRect; color: "black"
                  }
                  PropertyChanges {
                      target: indicText; text: "connecting if1moc..."
                  }
              }
          ]
      }



      Component {
          id: dndDelegate
          Item {
              id: wrapper
              width: view.cellWidth
              height: view.cellHeight
              Image {
                  id: itemImage
                  source: {
                      if(item_type != "") {
                          "qrc:/assets/" + item_type + "_" + item_color + ".png"
                      }
                      else {
                          ""
                      }
                  }

                  anchors.centerIn: parent
                  //smooth: true
                  //fillMode: Image.PreserveAspectFit
              }

              states: [
                  State {
                      name: "inDrag"
                      when: index == view.draggedFrom
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
                  }/*,
                  State {
                      name: "WHITEMOVE"
                      when: boardModel.getActivePlayer() === false
                      PropertyChanges {
                          target: indicRect; color: "white"
                      }
                      PropertyChanges {
                          target: indicText; text: ""
                      }
                  },
                  State {
                      name: "BLACKMOVE"
                      when: boardModel.getActivePlayer() === true
                      PropertyChanges {
                          target: indicRect; color: "black"
                      }
                      PropertyChanges {
                          target: indicText; text: ""
                      }
                  }*/
              ]
          }
      }

      GridView {
          id: view

          width: 480
          height: 480
          cellWidth: 60
          cellHeight: 60
          model: boardModel
          delegate: dndDelegate
          //verticalLayoutDirection: GridView.BottomToTop

          //property int draggedItemIndex: -1
          property int draggedFrom: -1
          property int draggedTo: -1

          interactive: false

          Item {
              id: dndContainer
              anchors.fill: parent
          }


          MouseArea {
              id: coords
              anchors.fill: parent

              onPressed: {
                    //view.draggedItemIndex = view.indexAt(mouseX, mouseY)
                  view.draggedFrom = view.indexAt(mouseX, mouseY)
              }

              onReleased: {
                  view.draggedTo = view.indexAt(mouseX, mouseY)

                  //boardModel.getActivePlayer()
                  if (view.draggedFrom !== view.draggedTo) {
                      boardModel.finishMove(view.draggedFrom, view.draggedTo)
                  }
              }
          }
       }
    }
}





































