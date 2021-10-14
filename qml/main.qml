import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

ApplicationWindow
{
    id: root
    maximumWidth: 1000
    minimumHeight: Screen.height
    minimumWidth: 1000
    x: Screen.width / 2 - width / 2
    visible: true
    title: qsTr("Colors")
    flags: Qt.FramelessWindowHint

    property bool showBonusColor: false

    header: ToolBar
    {
        id: toolBar
        visible: false

        ToolButton
        {
            icon.source: "qrc:/menu/resources/powerOff.png"
            onClicked: root.close()
        }

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
//                game.view.update();
                popup.open();
            }
        }
        ToolButton
        {
            anchors.right: stepDown.left
            anchors.verticalCenter: parent.verticalCenter
            onClicked:
            {
                showBonusColor = true;
            }
        }
    }

    background: Image {
        source: "qrc:/menu/resources/startFrame1.jpg"
    }

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
            if (winningScore == "darkgray")
            {
                result.winnerText = "No winners!"
            }
            else
            {
                result.winnerText = "Your color is the best!"
            }

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
