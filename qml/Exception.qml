import QtQuick 2.0
import QtQuick.Controls 2.2

Dialog  {
    Text {
        visible: true
        anchors.centerIn: parent
        text: qsTr("The program terminated unexpectedly")

        ToolButton
        {
            icon.source: "qrc:/menu/resources/powerOff.png"
            onClicked: root.close()
        }
    }

}
