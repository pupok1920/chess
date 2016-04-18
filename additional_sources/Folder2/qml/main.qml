import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.5

ApplicationWindow
{
    property int squareSize: 32

    width: field.width
    height: field.width
    visible: true

    Item
    {
      id: field
      x: 0
      y: 0

      width: game.worldSize * squareSize;
      height: game.worldSize * squareSize;

      Rectangle
      {
          width: parent.width
          height: parent.height
          color: "black"
      }

      SoundEffect{ id: sound; source : "assets/sounds/explode.wav" }

      Repeater
      {
          model: game

          AnimatedSprite
          {
            x: posX * squareSize
            y: posY * squareSize
            width: squareSize
            height: squareSize

            property var spriteModels: [
              {'image' : "assets/graphics/bullet.png"    ,'frameCount': 1 , 'loops' : AnimatedSprite.Infinite},
              {'image' : "assets/graphics/wall1.png"     ,'frameCount': 1 , 'loops' : AnimatedSprite.Infinite},
              {'image' : "assets/graphics/wall2.png"     ,'frameCount': 1 , 'loops' : AnimatedSprite.Infinite},
              {'image' : "assets/graphics/home.png"      ,'frameCount': 1 , 'loops' : AnimatedSprite.Infinite},
              {'image' : "assets/graphics/redtank.png"   ,'frameCount': 8 , 'loops' : AnimatedSprite.Infinite},
              {'image' : "assets/graphics/greentank.png" ,'frameCount': 8 , 'loops' : AnimatedSprite.Infinite},
              {'image' : "assets/graphics/explosion.png" ,'frameCount': 16, 'loops' : 1                      },
            ]

            frameDuration: 100

            Component.onCompleted: 
            {
              index = Qt.binding(function() { return dead ? spriteModels.length - 1 : type; })
            }
            property int index: 0

            reverse: true
            frameCount: spriteModels[index].frameCount
            source: spriteModels[index].image
            loops: spriteModels[index].loops

            transform: Rotation { origin.x: squareSize/2; origin.y: squareSize/2;  angle: 90 + (arg * 180) / 3.1415926 }

            property var explosion: dead

            onExplosionChanged:
            {
              if(!dead) return;
              restart();
              currentFrame = 0;
              sound.play();
            }
          }
      }

      Image
      {
        source: "assets/graphics/gameover.png"
        anchors.centerIn: parent
        visible: game.gameOver
      }

      focus: true

      Keys.onPressed: {
        if(game.gameOver)
            game.start()
      }
    }

    Component.onCompleted: {
        title = Qt.binding(function() { 
            if(!game.gameOver) {
              return qsTr("exit: esc  fire: space   enemy left: " + game.enemyLeft); 
            }
            return qsTr("to start new game press any key"); 
        })
    }

}
