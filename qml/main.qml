import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

ApplicationWindow
{
    id: root
    maximumWidth: 900
    maximumHeight: 800
    minimumHeight: 800
    minimumWidth: 900
    visible: true
    title: qsTr("Colors")

    property int showBonusColor: 0

    header: ToolBar
    {
        id: toolBar
        visible: false

        ToolButton
        {
            id: stepDown
            anchors.right: restart.left
            icon.source: "qrc:/menu/resources/StepBack.jpg"
            anchors.verticalCenter: parent.verticalCenter
            onClicked:
            {
                game.stepDown();
            }
        }

        ToolButton
        {
            id: restart
            anchors.right: parent.right
            icon.source: "qrc:/menu/resources/Restart.jpg"
            anchors.verticalCenter: parent.verticalCenter
            onClicked:
            {
                game.visible = false;
                popup.open();
            }
        }
        ToolButton
        {
            anchors.right: stepDown.left
            anchors.verticalCenter: parent.verticalCenter
            onClicked:
            {
                showBonusColor = 1;
            }
        }
    }


//    flags: Qt.FramelessWindowHint
//    CheckBox
//    {
//        id: framelessMode

//        anchors.left: root.l
//        text: qsTr("Frameless Mode")
//    }

    StartFrame
    {
        id: startFrame
        anchors.fill: parent
        onButtonClicked:
        {
            popup.open();
        }
    }

    GameSettings
    {
        id: popup
    }

    GameBoard
    {
        id: game
        visible: false
        boardSize: popup.boarderSize
        numberOfColors: popup.numberOfColors
        onGameIsOver:
        {
            result.visible = true;
            result.winnerColor = winningScore;
        }
    }

    Result
    {
        id: result
        visible: false
    }

    function checkState(currentPlayer)
    {
        if(popup.currentPlayerNum === 0)
        {
            game.fPlayerColor = currentPlayer;
            popup.currentPlayerNum = 1;
        }
        else
        {
            game.sPlayerColor = currentPlayer;
            popup.currentPlayerNum = 0;
            popup.close();
            toolBar.visible = true;
        }
    }
}
