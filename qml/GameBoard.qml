import QtQuick 2.12
import Game 1.0
import QtQuick.Layouts 1.1

Item
{
    id: _item
    signal dialogClose();
    signal gameIsOver()

    anchors.fill: parent

    property color fPlayerColor: "darkred"
    property color sPlayerColor: "blue"
    property int boardSize: 3
    property int numberOfColors: 3
    property color winningScore: "white"

//    property alias firstPlayerAccount: showPanel.firstPlayerAccount
//    property alias secondPlayerAccount: showPanel.secondPlayerAccount

    TableView {
        id: view

        anchors.fill: parent
        anchors.topMargin: 30
        model: GameBoardModel
        {
            onGameEndSignal:
            {
                if (view.firstPlayerAccount > view.secondPlayerAccount)
                    winningScore = _item.fPlayerColor;
                else
                    winningScore = _item.sPlayerColor;
                _item.gameIsOver();
            }
        }

//        Component.onCompleted:
//        {
////            showPanel.firstPlayerAccount: view.model.firstPlayerAccount;
////            showPanel.secondPlayerAccount = view.model.secondPlayerAccount;
//        }

        property alias firstPlayerAccount: showPanel.firstPlayerAccount
        property alias secondPlayerAccount: showPanel.secondPlayerAccount

        firstPlayerAccount: view.model.firstPlayerAccount
        secondPlayerAccount: view.model.secondPlayerAccount


        delegate: Item
        {
            id: _backgroundDelegate
            implicitWidth: view.width / view.model.nRows
            implicitHeight: view.height / view.model.nColumns

            Tile
            {
                id: _tile
                anchors.fill: _backgroundDelegate
                newColor: display

                Text {
                    id: name
                    anchors.centerIn: _tile
                    text: owner
                }
                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
console.log(view.firstPlayerAccount);
                        view.model.commit(row, column);
                        updateState();
                    }

                    onWheel:
                    {
                        view.model.stepDown();
                        updateState();
                    }
                }
            }
        }
    }


    PanelForDisplayingWhoseMove
    {
        id: showPanel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 30
        anchors.rightMargin: 30
    }

    function updateState()
    {
        if(view.model.state === 1)
        {
            showPanel.fieldForFirst.color = "black";
            showPanel.fieldForFirst.width = 1;
            showPanel.fieldForSecond.color = "cyan";
            showPanel.fieldForSecond.width = 5;
        }
        else
        {
            showPanel.fieldForFirst.color = "cyan";
            showPanel.fieldForFirst.width = 5;
            showPanel.fieldForSecond.color = "black";
            showPanel.fieldForSecond.width = 1;
        }
    }

    onDialogClose:
    {
        visible = true;
        view.model.boardCreation(boardSize, fPlayerColor, sPlayerColor, numberOfColors);
    }
}
