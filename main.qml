import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.1

import Veteran 1.0
import Qt.labs.platform 1.0
import QtGraphicalEffects 1.0


import "QChart.js" as Charts
import "QChartGallery.js" as ChartsData

ApplicationWindow {

    id: window
    width: 1024
    height: 600
    visible: true
    title: document.fileName + " - Text Editor Example"

    DocumentHandler {
        id:document
        document: textArea.textDocument
        cursorPosition: textArea.cursorPosition
        selectionStart: textArea.selectionStart
        selectionEnd: textArea.selectionEnd
        textColor: textArea.color
//        Component.onCompleted: document.load()
        onLoaded: {
            textArea.text = text
        }
        onError: {
            errorDialog.text = message
            errorDialog.visible = true
        }
    }

    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }

    Shortcut {
        sequence: StandardKey.Open
        onActivated: openDialog.open()
    }
    Shortcut {
        sequence: StandardKey.SaveAs
        onActivated: saveDialog.open()
    }
    Shortcut {
        sequence: StandardKey.Quit
        onActivated: Qt.quit()
    }
    Shortcut {
        sequence: StandardKey.Copy
        onActivated: textArea.copy()
    }
    Shortcut {
        sequence: StandardKey.Cut
        onActivated: textArea.cut()
    }
    Shortcut {
        sequence: StandardKey.Paste
        onActivated: textArea.paste()
    }
    Shortcut {
        sequence: StandardKey.Bold
        onActivated: document.bold = !document.bold
    }
    Shortcut {
        sequence: StandardKey.Italic
        onActivated: document.italic = !document.italic
    }
    Shortcut {
        sequence: StandardKey.Underline
        onActivated: document.underline = !document.underline
    }


    FileDialog {
        id: openDialog
        fileMode: FileDialog.OpenFile
        selectedNameFilter.index: 1
        nameFilters: ["Text files (*.txt)", "HTML files (*.html *.htm)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: document.load(file)
    }

    FileDialog {
        id: saveDialog
        fileMode: FileDialog.SaveFile
        defaultSuffix: document.fileType
        nameFilters: openDialog.nameFilters
        selectedNameFilter.index: document.fileType === "txt" ? 0 : 1
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: document.saveAs(file)
    }

    FontDialog {
        id: fontDialog
        onAccepted: {
            document.fontFamily = font.family;
            document.fontSize = font.pointSize;
        }
    }

    ColorDialog {
        id: colorDialog
        currentColor: "black"
    }

    MessageDialog {
        id: errorDialog
    }

    header: ToolBar {
        leftPadding: 8
        Flow {
            id: flow
            width: parent.width - 100
            Row {
                id:drawerRow
                ToolButton {
                    id: toolButton
                    text: stackView.depth > 1 ? "\u25C0" : "\u2630"
                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                    onClicked: {
                        if (stackView.depth > 1) {
                            stackView.pop()
                        } else {
                            drawer.open()
                        }
                    }
                }
                ToolSeparator {
                    contentItem.visible: fileRow.y === editRow.y
                }
            }

            Row {
                id: fileRow
                ToolButton {
                    id: openButton
                    text: "\uF115" // icon-folder-open-empty
                    font.family: "fontello"
                    onClicked: openDialog.open()
                }
                ToolSeparator {
                    contentItem.visible: fileRow.y === editRow.y
                }
            }

            Row {
                id: editRow
                Label {
                    text: stackView.currentItem.title
                    anchors.centerIn: parent
                }

                ToolButton {
                    id: copyButton
                    text: "\uF0C5" // icon-docs
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    enabled: textArea.selectedText
                    onClicked: textArea.copy()
                }
                ToolButton {
                    id: cutButton
                    text: "\uE802" // icon-scissors
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    enabled: textArea.selectedText
                    onClicked: textArea.cut()
                }
                ToolButton {
                    id: pasteButton
                    text: "\uF0EA" // icon-paste
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    enabled: textArea.canPaste
                    onClicked: textArea.paste()
                }
                ToolSeparator {
                    contentItem.visible: editRow.y === formatRow.y
                }
            }

            Row {
                id: formatRow
                ToolButton {
                    id: boldButton
                    text: "\uE800" // icon-bold
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    checkable: true
                    checked: document.bold
                    onClicked: document.bold = !document.bold
                }
                ToolButton {
                    id: italicButton
                    text: "\uE801" // icon-italic
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    checkable: true
                    checked: document.italic
                    onClicked: document.italic = !document.italic
                }
                ToolButton {
                    id: underlineButton
                    text: "\uF0CD" // icon-underline
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    checkable: true
                    checked: document.underline
                    onClicked: document.underline = !document.underline
                }
                ToolButton {
                    id: fontFamilyToolButton
                    text: qsTr("\uE808") // icon-font
                    font.family: "fontello"
                    font.bold: document.bold
                    font.italic: document.italic
                    font.underline: document.underline
                    onClicked: {
                        fontDialog.currentFont.family = document.fontFamily;
                        fontDialog.currentFont.pointSize = document.fontSize;
                        fontDialog.open();
                    }
                }
                ToolButton {
                    id: textColorButton
                    text: "\uF1FC" // icon-brush
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    onClicked: colorDialog.open()

                    Rectangle {
                        width: aFontMetrics.width + 3
                        height: 2
                        color: document.textColor
                        parent: textColorButton.contentItem
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.baseline: parent.baseline
                        anchors.baselineOffset: 6

                        TextMetrics {
                            id: aFontMetrics
                            font: textColorButton.font
                            text: textColorButton.text
                        }
                    }
                }
                ToolSeparator {
                    contentItem.visible: formatRow.y === alignRow.y
                }
            }

            Row {
                id: alignRow
                ToolButton {
                    id: alignLeftButton
                    text: "\uE803" // icon-align-left
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    checkable: true
                    checked: document.alignment == Qt.AlignLeft
                    onClicked: document.alignment = Qt.AlignLeft
                }
                ToolButton {
                    id: alignCenterButton
                    text: "\uE804" // icon-align-center
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    checkable: true
                    checked: document.alignment == Qt.AlignHCenter
                    onClicked: document.alignment = Qt.AlignHCenter
                }
                ToolButton {
                    id: alignRightButton
                    text: "\uE805" // icon-align-right
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    checkable: true
                    checked: document.alignment == Qt.AlignRight
                    onClicked: document.alignment = Qt.AlignRight
                }
                ToolButton {
                    id: alignJustifyButton
                    text: "\uE806" // icon-align-justify
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    checkable: true
                    checked: document.alignment == Qt.AlignJustify
                    onClicked: document.alignment = Qt.AlignJustify
                }
                ToolSeparator {
                    contentItem.visible: formatRow.y === alignRow.y
                }
            }
            Row{
                id:searchRow
                ToolButton {
                    id: searchButton
                    text: "Find" // icon-align-justify
                    font.family: "fontello"
                    checkable: true
                    onClicked: searchWindow.show()
                }
            }
        }
    }

    Flickable {
        id: flickable
        flickableDirection: Flickable.VerticalFlick
        anchors.fill: parent

        TextArea.flickable: TextArea {
            id: textArea
            textFormat: Qt.RichText
            wrapMode: TextArea.Wrap
            focus: true
            selectByMouse: true
            persistentSelection: true
            // Different styles have different padding and background
            // decorations, but since this editor is almost taking up the
            // entire window, we don't need them.
            leftPadding: 6
            rightPadding: 6
            topPadding: 20
            bottomPadding: 0
            background: null

            MouseArea {
                acceptedButtons: Qt.RightButton
                anchors.fill: parent
                onClicked: contextMenu.open()
            }

            onLinkActivated: Qt.openUrlExternally(link)
        }

        ScrollBar.vertical: ScrollBar {}
    }


    Drawer {
        id: drawer
        width: window.width * 0.33
        height: window.height

//        Column {
//            anchors.fill: parent

//            ItemDelegate {
//                text: qsTr("Page 1")
//                width: parent.width
//                onClicked: {
//                    stackView.push("Page1Form.ui.qml")
//                    drawer.close()
//                }
//            }
//            ItemDelegate {
//                text: qsTr("Page 2\n\nYesterDay")
//                width: parent.width
//                onClicked: {
//                    stackView.push("Page2Form.ui.qml")
//                    drawer.close()
//                }
//            }
//        }
        ListView {
            width:parent.width
            height: parent.height
            model:ContactModel {}

            delegate: Button {
                text: "\n" + name + "\n"
                onClicked: clickedDrawerItem(name)
            }
        }
    }

    StackView {
        id: stackView
//        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
    }

    function clickedDrawerItem(name)
    {
       drawer.close()
       textArea.text = document.load("qrc:files/"+name)
    }

    function getData()
    {
//        console.log(document.searchCounts)
//        console.log(document.searchTime)

        var s1 = document.searchCounts[0]
        var b1 = document.searchCounts[1]
        var a1 = document.searchCounts[2]
        var h1 = document.searchCounts[3]
        var r1 = document.searchCounts[4]

        var s2 = document.searchTime[0]
        var b2 = document.searchTime[1]
        var a2 = document.searchTime[2]
        var h2 = document.searchTime[3]
        var r2 = document.searchTime[4]

        var ChartBarData = {
              labels: ["Sequential (count*100)","Binary","AVL","Hash","RBTree"],
                datasets: [{
                  fillColor: "rgba(246,166,37,1)",
                strokeColor: "rgba(220,220,220,1)",
                       data: [s1, b1, a1, h1, r1]
            }, {
                  fillColor: "rgba(191,89,62,1)",
                strokeColor: "rgba(151,187,205,1)",
                       data: [s2, b2, a2, h2, r2]
            }]
        }
        return ChartBarData
    }

    Window {
        id:searchWindow
        width : 800
        height : 600
        visible: false


        Image{
            id:image
            source:"qrc:/images/xiaoxin.jpg"
            x: searchInput.x + 50
            y: searchInput.y - 250
        }

        LineInput {
            id:searchInput
            onInputText :  {
                if(flag == true) {
                    chart_bar.visible = false
                    document.input = searchInput.text;
                    chart_bar.chartData = getData()
                    chart_bar.repaint()
                    chart_bar.visible = true
                    if(moveFlag == false) {
                        searchInput.y -= 100
                        moveFlag = true
                    }

                    image.visible = false
                    console.log("zheli " + chart_bar.chartData.datasets[1].data)
                }
            }
            Behavior on y {PropertyAnimation {duration: 400} }
        }

        DropShadow {
            anchors.fill: searchInput
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 16
            color: "#80000000"
            source:searchInput
        }

        QChart {
            id: chart_bar;
            width:searchInput.width
            height: 250
            visible: false
            chartAnimated: true;
            anchors {left: parent.left; leftMargin: searchInput.x;bottom: result.top; bottomMargin: 50}
            chartAnimationEasing: Easing.OutBounce;
            chartAnimationDuration: 1000;
            chartType: Charts.ChartType.BAR;
            chartData: getData()

        }

        Text {
            id:result;
            width:searchInput.width;
            anchors {left: parent.left; leftMargin: searchInput.x;bottom:parent.bottom;bottomMargin:20}
            text:document.result
        }
    }

}

//Window {
//    visible: true
//    width:400
//    height:400
//    Item {
//        id: container
//        width: 320
//        height: 120

//        Rectangle {
//            id: rect
//            color: "red"
//            width: 120
//            height: 120

//            MouseArea {
//                anchors.fill: parent
//                onClicked: container.state == 'other' ? container.state = '' : container.state = 'other'
//            }
//        }
//        states: [
//            // This adds a second state to the container where the rectangle is farther to the right

//            State { name: "other"

//                PropertyChanges {
//                    target: rect
//                    x: 200
//                    y: 100
//                    color:"blue"
//                }
//            }
//        ]
//        transitions: [
//            // This adds a transition that defaults to applying to all state changes

//            Transition {

//                // This applies a default NumberAnimation to any changes a state change makes to x or y properties
//                NumberAnimation { properties: "x,y" }
//            }
//        ]
//    }

//}



//window containing the application
//ApplicationWindow {

//    //title of the application
//    title: qsTr("Hello World")
//    width: 640
//    height: 480
//    visible: true

//    //menu containing two menu items
//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("File")
//            MenuItem {
//                text: qsTr("&Open")
//                onTriggered: console.log("Open action triggered");
//            }
//            MenuItem {
//                text: qsTr("Exit")
//                onTriggered: Qt.quit();
//            }
//        }
//    }

//    //Content Area

//    //a button in the middle of the content area
//    Button {
//        text: qsTr("Hello World")
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.verticalCenter: parent.verticalCenter
//    }
//}

//Window {
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("Hello World")

//    ListView {
//        id: listView1
//        x:100
//        y:100
//        width:100
//        height:100
//        delegate: Item {

//            Rectangle {
//                id:cellRect

//                border.width: 10
//                border.color: "#D9D9D9"

//                Text {
//                    id:itemText
//                    text: name
//                    anchors.verticalCenter: parent.verticalCenter
//                }
//            }
//        }
//        model: ListModel {
//            id:testModel
//            ListElement {
//                name: "成都"
//            }
//        }
//        MouseArea {
//            anchors.fill:parent
//            onClicked: itemText.text + "1"
//            hoverEnabled: itemText.text + "2"
//        }
//    }
//}

//    Item {
//        id: root

//        width: 320
//        height: 480

//        Rectangle {
//            color: "#272822"
//            width: 320
//            height: 480
//        }

//        Rectangle {
//            id: rectangle
//            x: 40
//            y: 20
//            width: 120
//            height: 120
//            color: "red"

//            MouseArea {
//                anchors.fill: parent
//                onClicked: rectangle.width += 10
//            }
//        }
//    }
//}
