import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    Layout.fillWidth: true

    RowLayout {
        id: login_area
        anchors.centerIn: parent

        TextArea {
            Layout.fillWidth: true
            wrapMode: TextArea.Wrap
            placeholderText: qsTr("Create a username...")

            text: client.uname
            onTextChanged: client.uname = text
        }

        Button {
            text: qsTr("Launch")
            enabled: client.uname.length > 0
            onClicked: {
                client.login_err = ""           // Clear error message
                console.log("Creating user: " + client.uname)
                socket.active = true            // Connect chat client to chat server
            }
        }
    }

    // Error message to show on non-unique username
    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: login_area.bottom
        }
        color: "red"
        text: client.login_err
    }
}
