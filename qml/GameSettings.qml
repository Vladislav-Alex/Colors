import QtQuick 2.15
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1

Popup {
    property int boarderSize: spin1.value
    property int numberOfColors: spin2.value
    property int currentPlayerNum: page.currentPlayerNum

    id: popup
    anchors.centerIn: parent
    width: root.width / 2
    height: root.height / 1.5
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    background:  Image {
        source: "qrc:/menu/resources/startFrame1.jpg"
    }
    padding: 0

    Rectangle {
        id: page
        anchors.fill: parent
        color: "steelblue"

        opacity: 0.65
        property int currentPlayerNum: 0;
        property color currentPlayer: "white"

        Text
        {
            id: helloText
            text: "Welcome!"
            y: 50
            anchors.horizontalCenter: page.horizontalCenter
            font.pointSize: 24
            font.bold: true

            Text
            {
                anchors.top: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "(Choose some settings)\nEnd enter esc to accept it."
                font.pointSize: 8
            }
        }

        ColumnLayout
        {
            anchors.verticalCenter: parent.verticalCenter
            Text
            {
                anchors.verticalCenter: popup.verticalCenter
                text: "Board size:"
                font.pointSize: 10

                SpinBox {
                    id: spin1
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.right
                    anchors.leftMargin: 50
                    from: 5
                    to: 50
                    value: 20
                }
            }

            Text
            {
                anchors.verticalCenter: popup.verticalCenter
                text: "Number Of Colors:"
                font.pointSize: 10

                SpinBox {
                    id: spin2
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.right
                    anchors.leftMargin: 10
                    from: 3
                    to: 10
                    value: 3
                }
            }
        }

        Grid {
            id: colorPicker
            anchors.right: page.right
            anchors.bottom: page.bottom;
            anchors.bottomMargin: 7
            anchors.rightMargin: 7
            rows: 2;
            columns: 4;
            spacing: 3

            Cell { id: c1; cellColor: "red"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { id: c2; cellColor: "green"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { id: c3; cellColor: "yellow"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { id: c4; cellColor: "steelblue"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { id: c5; cellColor: "white"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { id: c6; cellColor: "blue"; onClicked: { checkState(cellColor); visible = false; } }

            Cell { id: black; cellColor: "black"; visible: false;  onClicked: { checkState(cellColor); visible = false; } }
            }
    }

    onOpened:
    {
        c1.visible = true;
        c2.visible = true;
        c3.visible = true;
        c4.visible = true;
        c5.visible = true;
        c6.visible = true;
        if (showBonusColor === 1)
        {
            black.visible = true;
        }
    }

    onClosed:
    {
        game.dialogClose();
//        game.boardSize = boarderSize;
        startFrame.visible = false;
        game.updateState();
    }
}
