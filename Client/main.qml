import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.15

Window {
    width: 340
    height: 580
    visible: true
    title: qsTr("CHAT")

    Connections{
        target: appCore

        onAddMessage:{
            tEdit.text += _message + "\n"
            message_str.text = ""
//            console.log("_message:", _message );
        }
    }


    RowLayout {
        width: parent.width
        height: Math.min(parent.width, parent.height)

        anchors.fill: parent
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top:  parent.bottom
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        GridLayout {
            Layout.minimumHeight: parent.height
            Layout.minimumWidth: parent.width

            Label {
                text: qsTr("Имя: ")

                Layout.row: 0
                Layout.column: 0
                font.pointSize: 15
            }

            TextInput {
                id: name
                Layout.row: 0
                Layout.column: 1
                Layout.fillWidth: true

                font.pointSize: 15

                focus: true
            }

            Rectangle {
                id: rect

                Layout.row: 1
                Layout.column: 0
                Layout.columnSpan: 2

                border.color: "gray"
                color: "#cccccc"
                radius: 15

                Layout.fillWidth: true
                Layout.fillHeight:  true

                TextEdit{
                    id: tEdit

                    anchors.fill: parent
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.top:  parent.bottom
                    anchors.topMargin: 10
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10

                    enabled: false

//                    text: "<b>Hello</b> <i>World!</i>"
                    font.family: "Helvetica"
                    font.pointSize: 15
                    color: "blue"
                    focus: true
                }
            }

            Label {
                text: qsTr("Сообщение: ")

                Layout.row: 2
                Layout.column: 0
                font.pointSize: 15
            }

            TextInput {
                id: message_str

                Layout.row: 2
                Layout.column: 1
                Layout.fillWidth: true

                font.pointSize: 15

                focus: true
            }

            Button {
                id: send_btn
                text: "Отправить"

                Layout.row: 3
                Layout.column: 0
                Layout.columnSpan: 2

                Layout.fillWidth: true

                font.pointSize: 15
                background: Rectangle {
                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
                    border.color: "#26282a"
                    border.width: 2
                    radius: 15
                }
                onClicked: {
                    appCore._message = name.text + ":" + message_str.text

                    appCore.on_send_clicked()
                }
            }
        }
    }
}
