import QtQuick 2.15
import QtQuick.Layouts 1.1

GridLayout
{
    property int firstPlayerAccount: 0
    property int secondPlayerAccount: 0

    property alias fieldForFirst: _fieldForFirst.border
    property alias fieldForSecond: _fieldForSecond.border
    id: _layout

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
            text: firstPlayerAccount
        }
    }
    Rectangle
    {
        id: _fieldForSecond
        height: 25
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: _item.sPlayerColor

        radius: 4

        border.color: "black"
        border.width: 1

        Text
        {
            id: _textSecondPl
            anchors.right: _fieldForSecond.right
            anchors.rightMargin: 10
            font.family: "Helvetica"
            font.pointSize: 16
            text: secondPlayerAccount
        }
    }
}
