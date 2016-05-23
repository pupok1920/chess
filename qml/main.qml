import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.5
import QtQml.Models 2.2
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

    Item {
      id: field

      width: 480
      height: 480

      Image {
          id: board
          anchors.fill: parent
          source: "qrc:/assets/board.jpg"
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

      GridView {
          id: view

          width: 480
          height: 480
          cellWidth: 60
          cellHeight: 60
          model: boardModel
          delegate: dndDelegate

          property int draggedItemIndex: -1

          interactive: false

          Item {
              id: dndContainer
              anchors.fill: parent
          }

          MouseArea {
              id: coords
              anchors.fill: parent
              /*onReleased: {
                    if (view.draggedItemIndex != -1 &&
                            view.draggedItemIndex >= 0 &&
                            view.draggedItemIndex < view.count &&
                            view.draggedItemIndex != view.indexAt(mouseX, mouseY)
                            ) {
                        var sss = view.model.get(view.draggedItemIndex).source
                        view.model.set(view.indexAt(mouseX, mouseY), {"source":sss})
                        view.model.set(view.draggedItemIndex, {"source":""})
                    }
              }*/

              onPressed: {
                    view.draggedItemIndex = view.indexAt(mouseX, mouseY)
              }
          }
       }
    }
}





































