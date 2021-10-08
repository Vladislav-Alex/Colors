import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Item
{
    id: _item
    anchors.fill: parent

    signal buttonClicked()

    ColumnLayout
    {
        id: _column
        height: 60

        anchors.left: _item.left
        anchors.right: _item.right
        anchors.bottom: _item.verticalCenter
        anchors.margins: 15

        spacing: 20

        ToolButton
        {
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true

            implicitHeight: 20
            text: qsTr("Single_Play")

            onClicked:
            {
                _item.buttonClicked()
            }
        }

        ToolButton
        {
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true

            implicitHeight: 20
            text: qsTr("Game")
            onClicked:
            {
                _item.buttonClicked()
            }
        }
    }

    ToolButton
    {
        height: 20
        anchors.bottom: _item.bottom
        anchors.left: _item.left
        anchors.right: _item.right
        anchors.margins: 15

        text: qsTr("Exit")
        onClicked: Qt.quit();
    }
}

