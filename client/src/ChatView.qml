import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    title: qsTr("Connected User B")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: "\u276E"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                    stackView.pop()
                    drawer.open()
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
            padding: 10
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        ToolButton {
            id: closeButton
            anchors {
                right: parent.right
                rightMargin: 20
            }
            text: "\u00d7"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: stackView.pop()
        }
    }

    ScrollView {
        id: chatTranscriptScroll
        anchors.fill: parent

        //hint from email:
//        TextEdit {
//            id: chatTranscriptText
//            width: chatTranscriptScroll.width
//            readOnly: true
//            textFormat: Text.RichText // enables HTML formatting
//            wrapMode: TextEdit.Wrap
//        }

        ListView {
            model: 20
            contentHeight: toolButton.implicitHeight
            width: parent.width
            delegate: ItemDelegate {
                width: parent.width
                Text {
                    id: message
                    anchors {
                        left: parent.left
                        leftMargin: 20
                    }
                    width: parent.width - 80
                    text: "Lorem ipsum text here...some message that was sent...Lorem ipsum text here...some message that was sent...Lorem ipsum text here...some message that was sent...";
                    wrapMode: Text.WordWrap
                }

                Text {
                    id: timeTag
                    anchors {
                        right: parent.right
                        rightMargin: 20
                    }
                    text: (index + 1) + ":00"//message.time;
                    color: "#CCC"
                }
            }
        }
    }

    footer:  Pane {
        id: inputBox
        Layout.fillWidth: true

        RowLayout {
            width: parent.width

            TextArea {
                id: messageField
                Layout.fillWidth: true
                placeholderText: qsTr("Type a message...")
                wrapMode: TextArea.Wrap
            }

            Button {
                id: sendButton
                text: qsTr("Send")
                enabled: messageField.length > 0
                onClicked: {
                    console.log("sending message...")
                }
            }
        }
    }

}
