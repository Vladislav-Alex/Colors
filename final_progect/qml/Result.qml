import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2


Dialog
{
    id: dialog
    anchors.centerIn: parent

    property color winnerColor: "white"
    width: 300
    height: 100
    Text
    {
        anchors.centerIn: parent
        text: qsTr("Your color is the best");
        color: winnerColor
    }
    Row
    {
        id: row
        width: 230
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        anchors.bottomMargin: 5
        spacing: 30
        Button
        {
            text: qsTr("Restart")
            onClicked:
            {
                game.visible = false;
                popup.open();
                dialog.close();
            }
        }
        Button
        {
            text: qsTr("Exit")
            onClicked: Qt.quit();
        }
    }
}



//Item {
//    id: root

//    property alias firstPlayerAccount: _textFirstPl.text
////    property alias secondPlayerAccount: _textSecondPl.text

//    GridLayout
//    {
//        id: _layout
//        anchors.left: root.left
//        anchors.right: root.right
//        anchors.leftMargin: 30
//        anchors.rightMargin: 30

//        columns: 2

//        Rectangle
//        {
////            id: _fieldForFirst
//            height: 25
//            Layout.fillWidth: true
//            Layout.fillHeight: true
//            color: "red"

//            radius: 4

//            border.color: "cyan"
//            border.width: 5

//            Text
//            {
//                id: _textFirstPl
//                anchors.left: _fieldForFirst.left
//                anchors.leftMargin: 10

//                font.family: "Helvetica"
//                font.pointSize: 16
//                text: accountFirstPlayer
//            }
//        }
//        Rectangle
//        {
//            id: _fieldForSecond
//            height: 25
//            Layout.fillWidth: true
//            Layout.fillHeight: true
//            color: "blue"

//            radius: 5

//            border.color: "black"
//            border.width: 1

//            Text
//            {
//                id: _textSecondPl
//                anchors.right: _fieldForSecond.right
//                anchors.rightMargin: 10
//                font.family: "Helvetica"
//                font.pointSize: 16
//                text: qsTr("100")
//            }
//        }
//    }
//}
//Item
//{
//    id: root
//    property int size: 100
//    property color color: "lightgrey"
//    property alias text: caption.text

//    signal clicked()

//    width: size
//    height: size

//    Rectangle
//    {
//        anchors.fill: parent
//        radius: size / 2
//        color: mouseArea.containsPress ? Qt.darker(root.color, 1.2) : root.color

//        Text {
//            id: caption
//            anchors.centerIn: parent
//            text: qsTr("clickme")
//        }

//        MouseArea
//        {
//            id: mouseArea
//            anchors.fill: parent
//            onClicked: root.clicked();
//        }
//    }
//}
