import QtQuick 2.0
import QtQuick.Controls 2.2

//FocusScope {
//    id: wrapper

//    property alias text: input.text //
//    property alias hint: hint.text //
//    property alias prefix: prefix.text //
//    property int font_size: 18 //定义字体大小

//    signal accepted

//    Rectangle {
//        anchors.fill: parent
//        border.color: "#707070"
//        color: "#c1c1c1"
//        radius: 4  //半径

//        Text {
//            id: hint  //水印层文字显示
//            anchors { fill: parent; leftMargin: 14 }
//            verticalAlignment: Text.AlignVCenter //垂直对齐
//            text: "Enter word"
//            font.pixelSize: font_size //字体大小
//            color: "#707070"
//            opacity: input.length ? 0 : 1 //不透明度
//        }

//        Text {
//            id: prefix
//            anchors { left: parent.left; leftMargin: 14; verticalCenter: parent.verticalCenter }
//            verticalAlignment: Text.AlignVCenter  //垂直对齐
//            font.pixelSize: font_size
//            color: "#707070"
//            opacity: !hint.opacity //和hint相反
//        }

//        TextInput {
//            id: input
//            focus: true
//            anchors { left: prefix.right; right: parent.right; top: parent.top; bottom: parent.bottom }
//            verticalAlignment: Text.AlignVCenter  //垂直对齐
//            font.pixelSize: font_size
//            //color: "#707070"
//            color: "black"
//            onAccepted: wrapper.accepted()  //链接到信号
//        }
//    }
//}

FocusScope {
    id: wrapper

    property alias text: input.text //
    property alias hint: hint.text //
    property alias prefix: prefix.text //
    property int font_size: 18 //定义字体大小
    property bool flag: false
    property bool moveFlag : false;

    signal inputText();

    width:parent.width * 0.7
    height:50
    x:parent.width/2 - width/2
    y:parent.height/2 - 100
    Rectangle {
        anchors.fill: parent
        border.color: "#DEDEDE"
        color: "white"
        width:parent.width
        id:searchRec

        Text {
            id: hint  //水印层文字显示
            anchors { fill: parent; leftMargin: 14 }
            verticalAlignment: Text.AlignVCenter //垂直对齐
            text: "Search Here"
            font.pixelSize: font_size //字体大小
            color: "#707070"
            opacity: input.length ? 0 : 1 //不透明度
        }

        Text {
            id: prefix
            anchors { left: parent.left; leftMargin: 14; verticalCenter: parent.verticalCenter }
            verticalAlignment: Text.AlignVCenter  //垂直对齐
            font.pixelSize: font_size
            color: "#707070"
            opacity: !hint.opacity //和hint相反
        }

        TextInput {
            id: input
            focus: true
            anchors {left: prefix.right;  top: parent.top; bottom: parent.bottom}
            width: 500
            verticalAlignment: Text.AlignVCenter  //垂直对齐
            font.pixelSize: font_size
            //color: "#707070"
            color: "black"
            onAccepted: wrapper.accepted()  //链接到信号
        }

        ToolButton {
            anchors{right:parent.right; rightMargin: 14}
            id:searchButton
            text:"Search"
            onClicked: {
                flag = true
                emit: inputText();
            }
        }

        ToolSeparator {
            anchors {right:searchButton.left}
            contentItem.visible: formatRow.y === alignRow.y
        }
    }
}
