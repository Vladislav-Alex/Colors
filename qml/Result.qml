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
                toolBar.visible = false;
            }
        }
        Button
        {
            text: qsTr("Exit")
            onClicked: Qt.quit();
        }
    }
}
