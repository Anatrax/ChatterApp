import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: "\u276E"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                drawer.open()
                stackView.pop()
            }
        }

        Label {
            text: client.cur_convo
            anchors.centerIn: parent
            padding: 10
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        ToolButton {
            anchors {
                right: parent.right
                rightMargin: 20
            }
            text: "\u00d7"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                client.cur_convo = ""
                stackView.pop()
            }
        }
    }

    ScrollView {
        id: chatTranscriptScroll
        anchors.fill: parent

        ListView {
            focus: true
            width: parent.width

            header: Label {
                text: "<b>Connected Users</b>"
                padding: 10
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            delegate: ItemDelegate {
                width: parent.width
                height: message.height + 20

                // Message
                Text {
                    id: message
                    anchors {
                        left: parent.left
                        leftMargin: 20
                    }
                    width: parent.width - 40 - timestamp.width
                    text: model.message
                    wrapMode: Text.WordWrap
                }

                // Timestamp
                Text {
                    id: timestamp
                    anchors {
                        right: parent.right
                        rightMargin: 20
                    }
                    text: model.timestamp
                    color: "#CCC"
                }
            }

            model: ListModel { id: message_list }

            Component.onCompleted: {
                // Load conversation from C++
                console.log("Loading messages for conversation with " + client.cur_convo + "...")
                console.log("Messages loaded: " + client.getConversation())
                message_list.append(JSON.parse(client.getConversation()));
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    footer:  Pane {
        id: inputBox
        Layout.fillWidth: true

        RowLayout {
            width: parent.width

            TextArea {
                id: message_area
                Layout.fillWidth: true
                placeholderText: qsTr("Type a message...")
                wrapMode: TextArea.Wrap
            }

            Button {
                text: qsTr("Send")
                enabled: message_area.text.length > 0
                onClicked: {
                    console.log("Sending message: \"" +message_area.text + "\"")
                    message_list.append({"message": "<b>You:</b> "+message_area.text, "timestamp": client.time})
                    console.log(client.addMessage("You", message_area.text, client.time))   //DEBUG

                    // Send message
                    //var client_message = JSON.stringify({type:'ADD_MESSAGE',message:message_area.text,author:client.uname});
                    //socket.sendTextMessage(client_message);

                    // Clear message area for next message
                    message_area.text = ""
                }
            }
        }
    }

}
