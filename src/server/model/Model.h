#ifndef COOPERATIVEEDITOR_MODEL_H
#define COOPERATIVEEDITOR_MODEL_H

#include <QVector>
#include <QString>
#include <map>
#include <mutex>
#include <memory>
#include <atomic>

#include "components/Symbol.h"

#include "ServerFile.h"
#include "Database.h"
#include "common/User.h"
#include "common/TcpSocket.h"

/**
 * Model server class
 */
class Model {

private:

    Database database;

    ///Set of all available files
    QVector<QString> availableFiles;

    ///The map of the current file for each user
    std::multimap<std::shared_ptr<ServerFile>, TcpSocket *> usersFile;

    ///The mutex for the usersFile map
    std::mutex usersFileMutex;

    ///Editor Id unique generator
    std::atomic<unsigned> idGenerator;

    ///Method to write on file the respective sequence of symbols
    static void storeFileSymbols(const std::shared_ptr<ServerFile> &serverFile);

    ///Method to restore from file the respective sequence of symbols
    static void loadFileSymbols(const std::shared_ptr<ServerFile> &serverFile);

public:
    ///Classic constructor
    Model();

    ///Method to handle user remote insertion
    void userInsert(TcpSocket *socket, Symbol symbol);

    ///Method to handle user remote deletion
    void userErase(TcpSocket *socket, Symbol symbol);

    void removeConnection(TcpSocket *socket);

    ///Method called when a user requests to create a file
    bool createFileByUser(TcpSocket *socket, const QString &filename);

    ///Method called when a user requests to open a file
    bool openFileByUser(TcpSocket *socket, QString filename);

    ///Returns the list (string) of all available files
    QVector<QString> &getAvailableFiles();

    ///Returns the list of symbols for the file the user connId has requested
    ServerFile &getFileBySocket(TcpSocket *socket);

    ///Returns a bool to indicate if the logIn credential are correct and set the User object
    bool logInUser(User &user);

    ///Returns a bool to indicate if the registration was successful
    bool registerUser(User &user);

    ///Returns a bool to indicate if the update was successful
    bool updateUser(User &user);

    ///Returns a bool to indicate if the update was successful
    bool deleteUser(User &user);

    std::vector<TcpSocket *> getFileConnections(const QString &fileName);
};


#endif //COOPERATIVEEDITOR_MODEL_H
