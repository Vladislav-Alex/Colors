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
                font.pointSize: 16
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
}

