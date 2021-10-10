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

    padding: 10

    contentItem: Text {
        text: "Content"
    }

    Rectangle {
        id: page
        anchors.fill: parent
        color: "lightgray"

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
                    value: 25
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

            Cell { cellColor: "red"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { cellColor: "green"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { cellColor: "yellow"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { cellColor: "steelblue"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { cellColor: "black"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { cellColor: "white"; onClicked: { checkState(cellColor); visible = false; } }
            Cell { cellColor: "blue"; onClicked: { checkState(cellColor); visible = false; } }
            }
    }
    onClosed:
    {
        game.dialogClose();
//        game.boardSize = boarderSize;
        startFrame.visible = false;
    }
}
