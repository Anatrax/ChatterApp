/**
 * @brief Implementation of Chat Client Backend
 * @author Samuel D. Villegas
 * @date April 2, 2020
 */
#include "Backend.h"

Backend::Backend(QObject* parent) : QObject(parent) {}

void Backend::setUname(const QString& uname){
    if (uname.toStdString() == this->data_model.uname)  // Safety check
        return;
    this->data_model.uname = uname.toStdString();       // Set username
    emit this->unameChanged();                          // Send signal to notify change
}

void Backend::setUID(const QString& uid){
    if (uid.toStdString() == this->data_model.uid)  // Safety check
        return;
    this->data_model.uid = uid.toStdString();       // Set user ID
    emit this->uidChanged();                        // Send signal to notify change
}

void Backend::setCurConvo(const QString& convo){
    if (convo.toStdString() == this->data_model.cur_convo)          // Safety check
        return;
    this->data_model.setCurrentConversation(convo.toStdString());   // Set current conversation
    emit this->currentConversationChanged();                        // Send signal to notify change
}

int Backend::addUser(const QString& uname){
    return this->data_model.addUser(uname.toStdString());
}

int Backend::addMessage(const QString& message){
    return this->data_model.addMessage(message.toStdString());
}

int Backend::addMessage(const QString& author, const QString& message){
    return this->data_model.addMessage(author.toStdString(), message.toStdString());
}

int Backend::addMessage(const QString& author, const QString& message, const QString& timestamp){
    return this->data_model.addMessage(author.toStdString(), message.toStdString(), timestamp.toStdString());
}

QString Backend::uname() const {
    return QString::fromStdString(this->data_model.uname);
}

QString Backend::uid() const {
    return QString::fromStdString(this->data_model.uid);
}

QString Backend::cur_convo() const {
    return QString::fromStdString(this->data_model.cur_convo);
}

QString Backend::time() const {
    return QString::fromStdString(this->data_model.getTimeStr());
}

QString Backend::getConversation() const {
    return QString::fromStdString(this->data_model.getConversation());
}
