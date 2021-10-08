import QtQuick 2.0

Item {
    id: container
    property alias cellColor: rectangle.color
    signal clicked()

    width: 70
    height: 45

    Rectangle {
        id: rectangle
        border.color: "white"
        anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: container.clicked()
    }
}
