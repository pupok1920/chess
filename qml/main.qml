import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.5
import QtQml.Models 2.2
import QtQuick.Dialogs 1.1

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

          Rectangle {
              id: indicRect
              width: 30
              height: 30
              border.color: "red"
              x: 120
          }
          Text {
              id: indicText
              text: "Any move"
              font.family: "Helvetica"
              font.pointSize: 20
              color: "black"
          }

          states: [
              State {
                  name: "WHITEMOVE"
                  when: boardModel.getActivePlayer() == false
                  PropertyChanges {
                      target: indicRect; color: "white"
                  }
                  PropertyChanges {
                      target: indicText; text: "white move"
                  }
              },
              State {
                  name: "BLACKMOVE"
                  when: boardModel.getActivePlayer() == true
                  PropertyChanges {
                      target: indicRect; color: "black"
                  }
                  PropertyChanges {
                      target: indicText; text: "black move"
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
                  }
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

                  boardModel.finishMove(view.draggedFrom, view.draggedTo)
                  //boardModel.getActivePlayer()
                    /*if (view.draggedItemIndex != -1 &&
                            view.draggedItemIndex >= 0 &&
                            view.draggedItemIndex < view.count &&
                            view.draggedItemIndex != view.indexAt(mouseX, mouseY)
                            ) {
                        var sss = view.model.get(view.draggedItemIndex).source
                        view.model.set(view.indexAt(mouseX, mouseY), {"source":sss})
                        view.model.set(view.draggedItemIndex, {"source":""})
                    }*/
              }
          }
       }
    }
}





































