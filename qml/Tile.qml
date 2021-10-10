import QtQuick 2.0

Rectangle
{
    id: root

    property var newColor: ""
    color: newColor

    radius: 10

    border.color: "black"
    border.width: 1

//    Text {
//        id: _firstText
//        anchors.centerIn: root

//        text: newColor
//        font
//        {
//            pointSize: Math.min(root.width, root.height) / 3
//            bold: true
//        }
//    }
}
