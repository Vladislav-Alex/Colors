import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Item
{
    id: item
    anchors.fill: parent

    signal buttonClicked()

    MouseArea
    {
        anchors.fill: parent


        RoundButton
        {
            anchors.centerIn: parent
            width: 100
            height: 100
            radius: 250

            Text
            {
                anchors.centerIn: parent
                text: "Start"
                font.pointSize: 14
                font.bold: true
                color: "green"
            }

            palette.button: "red"

            onClicked:
            {
                item.buttonClicked();
            }
        }

        onClicked: root.close();
    }

//    ColumnLayout
//    {
//        id: _column
//        height: 60

//        anchors.left: item.left
//        anchors.right: item.right
//        anchors.bottom: item.verticalCenter
//        anchors.margins: 15

//        spacing: 20

//        ToolButton
//        {
//            Layout.alignment: Qt.AlignCenter
//            Layout.fillWidth: true

//            implicitHeight: 20
//            text: qsTr("Single_Play")

////            icon.source: "qrc:/menu/resources/game.jpg"
////            background: Image {
////                id: name
////                source: "qrc:/menu/resources/game.jpg"
////            }
//            onClicked:
//            {
//                item.buttonClicked()
//            }
//        }

//        ToolButton
//        {
//            Layout.alignment: Qt.AlignCenter
//            Layout.fillWidth: true

//            implicitHeight: 20
//            text: qsTr("Game")
//            onClicked:
//            {
//                item.buttonClicked()
//            }
//        }
//    }

//    ToolButton
//    {
//        height: 20
//        anchors.bottom: item.bottom
//        anchors.left: item.left
//        anchors.right: item.right
//        anchors.margins: 15

//        text: qsTr("Exit")
//        onClicked: Qt.quit();
//    }
}

