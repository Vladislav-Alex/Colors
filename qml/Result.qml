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
    visible: true
    Text
    {
        anchors.centerIn: parent
        text: qsTr("Your color is the best");
        color: winnerColor
    }
    Item
    {
        anchors.fill: parent
        Row
        {
            id: row
            width: 230

            anchors.bottom: parent.bottom
            layoutDirection: Qt.RightToLeft
            spacing: 40

            Button
            {
                text: qsTr("Exit")
                onClicked: Qt.quit();
            }

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
        }
    }
}
