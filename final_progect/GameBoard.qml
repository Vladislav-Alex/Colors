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

    onDialogClose:
    {
        visible = true;
        view.model.test(boardSize, fPlayerColor, sPlayerColor, numberOfColors);
    }

    function updateState()
    {
        if(view.model.state === 1)
        {
            _fieldForFirst.border.color = "black";
            _fieldForFirst.border.width = 1;
            _fieldForSecond.border.color = "cyan";
            _fieldForSecond.border.width = 5;
        }
        else
        {
            _fieldForFirst.border.color = "cyan";
            _fieldForFirst.border.width = 5;
            _fieldForSecond.border.color = "black";
            _fieldForSecond.border.width = 1;
        }
    }

    TableView {
        id: view

        anchors.fill: parent
        anchors.topMargin: 30
        model: GameBoardModel
        {
            onSomeSignal:
            {
                if (view.firstPlayerAccount > view.secondPlayerAccount)
                    winningScore = _item.fPlayerColor;
                else
                    winningScore = _item.sPlayerColor;
                _item.gameIsOver();
            }

        }

        property alias firstPlayerAccount: _textFirstPl.text
        property alias secondPlayerAccount: _textSecondPl.text
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

    GridLayout
    {
        id: _layout
        anchors.left: _item.left
        anchors.right: _item.right
        anchors.leftMargin: 30
        anchors.rightMargin: 30

        columns: 2

        Rectangle
        {
            id: _fieldForFirst
            height: 25
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: _item.fPlayerColor

            radius: 4

            border.color: "cyan"
            border.width: 5

            Text
            {
                id: _textFirstPl
                anchors.left: _fieldForFirst.left
                anchors.leftMargin: 10

                font.family: "Helvetica"
                font.pointSize: 16
                text: accountFirstPlayer
            }
        }
        Rectangle
        {
            id: _fieldForSecond
            height: 25
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: _item.sPlayerColor

            radius: 5

            border.color: "black"
            border.width: 1

            Text
            {
                id: _textSecondPl
                anchors.right: _fieldForSecond.right
                anchors.rightMargin: 10
                font.family: "Helvetica"
                font.pointSize: 16
                text: qsTr("100")
            }
        }
    }
}
