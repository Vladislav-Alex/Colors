import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

ApplicationWindow
{
    id: root
//    visibility: Window.FullScreen
    maximumWidth: 1000
    minimumHeight: Screen.height
    minimumWidth: 1000
    x: Screen.width / 2 - width / 2
//    x: ScreenInfo.width / 2 - root.width / 2
//    y: 10
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
                console.log(Screen.height);
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

    background: Image {
        source: "qrc:/menu/resources/startFrame1.jpg"
    }
    flags: Qt.FramelessWindowHint
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
        numberOfStartingCells: popup.numberOfStartingCells
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
