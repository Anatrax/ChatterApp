import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    Layout.fillWidth: true

    RowLayout {
        anchors.centerIn: parent

        TextArea {
            id: usernameField
            Layout.fillWidth: true
            placeholderText: qsTr("Create a username...")
            wrapMode: TextArea.Wrap
        }

        Button {
            id: loginButton
            text: qsTr("Launch")
            enabled: usernameField.length > 0
            onClicked: {
                console.log("creating user...")
                stackView.push("NoChatView.qml")
            }
        }
    }
}
