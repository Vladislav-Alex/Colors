import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1

Window
{
    id: root
    maximumWidth: 900
    maximumHeight: 800
    minimumHeight: 800
    minimumWidth: 900
    visible: true
    title: qsTr("temp")

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
        }
    }
}
