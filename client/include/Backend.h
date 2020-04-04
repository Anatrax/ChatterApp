/**
 * @brief Definitions for the Chat Client Backend
 * @author Samuel D. Villegas
 * @date April 2, 2020
 */
#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "ClientData.h"
/**
 * @brief Chat Client Backend
 */
class Backend : public QObject
{
    // Qt Macros
    Q_OBJECT
    Q_PROPERTY(QString uname READ uname WRITE setUname NOTIFY unameChanged)
    Q_PROPERTY(QString uid READ uid WRITE setUID NOTIFY uidChanged)
    Q_PROPERTY(QString login_err READ login_err WRITE setloginErr NOTIFY loginErrChanged)
    Q_PROPERTY(QString cur_convo READ cur_convo WRITE setCurConvo NOTIFY currentConversationChanged)
    Q_PROPERTY(QString time READ time)

public:
    /**
     * @brief Backend constructor
     */
    explicit Backend(QObject* parent = nullptr);

    /**
     * @brief Sets the client's username
     * @param uname - The client's username
     */
    void setUname(const QString& uname);

    /**
     * @brief Gets the client's username
     * @returns client's username
     */
    QString uname() const;

    /**
     * @brief Sets the client's user ID
     * @param uid - The client's user ID
     */
    void setUID(const QString& uid);

    /**
     * @brief Gets the client's user ID
     * @returns client's user ID
     */
    QString uid() const;

    /**
     * @brief Sets the login error message
     * @param err_msg - The error message
     */
    void setloginErr(const QString& err_msg);

    /**
     * @brief Gets the login error message
     * @returns the login error message
     */
    QString login_err() const;

    /**
     * @brief Sets the name of the current conversation
     * @param uname - The username to converse with
     */
    void setCurConvo(const QString& uname);

    /**
     * @brief Gets the name of the current conversation
     * @returns username conversing with
     */
    QString cur_convo() const;

    /**
     * @brief Gets the current client time
     * @returns current time
     */
    QString time() const;

    /**
     * @brief Adds a user to the connected users list
     * @param uname - The name of the user to add
     * @returns 0 if user was added successfully, -1 otherwise
     */
    Q_INVOKABLE int addUser(const QString& uname);

    /**
     * @brief Removes a user from the connected users list
     * @param uname - The name of the user to remove
     * @returns 0 if user was removed successfully, -1 otherwise
     */
    Q_INVOKABLE int removeUser(const QString& uname);

    /**
     * @brief Adds client's message to the current conversation
     * @param message - The message to add
     * @returns 0
     */
    Q_INVOKABLE int addMessage(const QString& message);

    /**
     * @brief Adds a message to the author's conversation
     * @param message - The message to add
     * @param author - The author of the message
     * @returns 0 on success, -1 otherwise
     */
    Q_INVOKABLE int addMessage(const QString& author, const QString& message);

    /**
     * @brief Adds a message to the author's conversation
     * @param author - The author of the message
     * @param message - The message to add
     * @param timestamp - The message's timestamp
     * @returns 0 on success, -1 otherwise
     */
    Q_INVOKABLE int addMessage(const QString& author, const QString& message, const QString& timestamp);

    /**
     * @brief Gets the messages from the current conversation
     * @returns a JSON Object string of messages
     */
    Q_INVOKABLE QString getConversation() const;

    /**
     * @brief Clears all data and resets to default init state
     */
    Q_INVOKABLE void resetData();

signals:
    /**
     * @brief Send "client's username changed" signal
     */
    void unameChanged();

    /**
     * @brief Send "client's user ID changed" signal
     */
    void uidChanged();

    /**
     * @brief Send "login error message changed" signal
     */
    void loginErrChanged();

    /**
     * @brief Send "client's current conversation changed" signal
     */
    void currentConversationChanged();

private:
    ClientData data_model;  // Client data model
    QString login_err_msg;  // Login error message
};

#endif // BACKEND_H
